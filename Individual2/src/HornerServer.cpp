#include "HornerServer.h"
#include <iostream>
#include <sstream>

HANDLE HornerServer::ghMutex = CreateMutex(NULL, FALSE, NULL);

HornerServer::HornerServer(const std::string& pipeName) : m_running(true) {
    m_pipePath = "\\\\.\\pipe\\" + pipeName;
}

HornerServer::~HornerServer() {
    if (ghMutex) CloseHandle(ghMutex); //[cite: 1]
}

void HornerServer::start() {
    HANDLE hCmd = CreateThread(NULL, 0, controlThread, this, 0, NULL);
    if (hCmd) CloseHandle(hCmd);

    std::cout << "[SYSTEM] Server path: " << m_pipePath << std::endl;
    std::cout << ">>> SERVER STARTED. Type 'stop' to exit." << std::endl;

    while (m_running) {
        HANDLE hPipe = CreateNamedPipeA(m_pipePath.c_str(), PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);

        if (hPipe == INVALID_HANDLE_VALUE) continue;

        if (ConnectNamedPipe(hPipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED) {
            static int counter = 0;
            ClientData* data = new ClientData{ hPipe, ++counter };

            HANDLE hThread = CreateThread(NULL, 0, solverThread, (LPVOID)data, 0, NULL);
            if (hThread) CloseHandle(hThread);
        }
        else {
            CloseHandle(hPipe);
        }
    }
}

double HornerServer::calculateHorner(const std::vector<double>& coeffs, double x) {
    double result = 0;
    for (double c : coeffs) {
        result = result * x + c;
    }
    return result;
}

DWORD WINAPI HornerServer::controlThread(LPVOID lpParam) {
    HornerServer* server = static_cast<HornerServer*>(lpParam);
    std::string cmd;
    while (server->m_running) {
        std::cout << "server_cmd> ";
        if (!(std::cin >> cmd)) break;
        if (cmd == "stop") {
            server->m_running = false;
            std::cout << "[SYSTEM] Stopping server..." << std::endl;
            exit(0);
        }
    }
    return 0;
}

DWORD WINAPI HornerServer::solverThread(LPVOID lpParam) {
    ClientData* data = static_cast<ClientData*>(lpParam);
    char buffer[512];
    DWORD bytesRead;

    if (ReadFile(data->hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        std::string requestStr(buffer);

        std::stringstream ss(requestStr);
        double x;
        if (!(ss >> x)) x = 0;

        std::vector<double> coeffs;
        double c;
        while (ss >> c) coeffs.push_back(c);

        double result = calculateHorner(coeffs, x);

        WaitForSingleObject(ghMutex, INFINITE);
        std::cout << "\n[LOG] Client ID: " << data->clientId << " | Request: " << requestStr << std::endl;
        std::cout << "[LOG] Result: P(" << x << ") = " << result << std::endl;
        std::cout << "server_cmd> ";
        ReleaseMutex(ghMutex);

        std::string resStr = "P(" + std::to_string(x) + ") = " + std::to_string(result);
        DWORD written;
        WriteFile(data->hPipe, resStr.c_str(), (DWORD)resStr.length(), &written, NULL);
    }

    CloseHandle(data->hPipe); //[cite: 1]
    delete data;
    return 0;
}