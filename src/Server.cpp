#include "Server.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>

Server::Server(const Polynomial& p) : poly(p), running(true) {}

Server::~Server() {
    closesocket(serverSocket);
    WSACleanup();
}

bool Server::init(int port) {
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        return false;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.100.1");;
    server.sin_port = htons(port);

    if(bind(serverSocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        return false;
    }

    listen(serverSocket, SOMAXCONN);
    return true;
}

DWORD WINAPI handleClient(LPVOID param) {
    SOCKET clientSocket = (SOCKET)param;
    char buffer[1024];

    std::vector<double> coeffs = {1, -3, 2}; 
    Polynomial poly(2, coeffs);

    while(true) {
        int recv_size = recv(clientSocket, buffer, sizeof(buffer), 0);
        if(recv_size <= 0) break;
        buffer[recv_size] = '\0';

        std::string cmd(buffer);
        std::string response;

        if(cmd[0] == 'x') {
            double x = atof(cmd.substr(2).c_str());
            response = std::to_string(poly.evaluate(x));
        } else if(cmd[0] == 'd') {
            response = std::to_string(poly.getDegree());
        } else if(cmd[0] == 'c') {
            std::ostringstream oss;
            for(double coeff : poly.getCoeffs()) {
                oss << coeff << " ";
            }
            response = oss.str();
        } else if(cmd == "shutdown") {
            response = "Server shutting down...";
            send(clientSocket, response.c_str(), response.size(), 0);
            closesocket(clientSocket);
            ExitProcess(0); 
        } else {
            response = "Unknown command";
        }

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    closesocket(clientSocket);
    return 0;
}

void Server::run() {
    std::cout << "Server started...\n";
    sockaddr_in client;
    int c = sizeof(sockaddr_in);

    while(running) {
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);
        if(clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed\n";
            continue;
        }

        CreateThread(NULL, 0, handleClient, (LPVOID)clientSocket, 0, NULL);
    }
}

void Server::shutdown() {
    running = false;
}

int main() {
    std::vector<double> coeffs = {1, -3, 2}; // x^2 - 3x + 2
    Polynomial poly(2, coeffs);

    Server server(poly);
    if(server.init(8080)) {
        server.run();
    }
    return 0;
}
