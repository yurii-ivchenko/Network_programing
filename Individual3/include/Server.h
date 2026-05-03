#pragma once
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>
#include "ClientHandler.h"

class Server {
private:
    WSADATA wsaData;
    SOCKET listenSocket;
    sockaddr_in serverAddr;
    int port;
    std::vector<std::thread> threads;

public:
    Server(int port);
    ~Server();
    void start();
    void stop();
};
