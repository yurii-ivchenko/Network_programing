#ifndef HORNER_SERVER_H
#define HORNER_SERVER_H

#include <windows.h>
#include <vector>
#include <string>
#include <atomic>

class HornerServer {
public:
    HornerServer(const std::string& pipeName);
    ~HornerServer();
    void start();

private:
    std::string m_pipePath;
    std::atomic<bool> m_running;
    static HANDLE ghMutex;

    struct ClientData {
        HANDLE hPipe;
        int clientId;
    };

    static DWORD WINAPI solverThread(LPVOID lpParam);
    static DWORD WINAPI controlThread(LPVOID lpParam);
    static double calculateHorner(const std::vector<double>& coeffs, double x);
};

#endif