#include "Server.h"
#include <iostream>

Server::Server(int port) : port(port), listenSocket(INVALID_SOCKET) {
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(listenSocket, SOMAXCONN);
}

Server::~Server() {
    stop();
    WSACleanup();
}

void Server::start() {
    std::cout << "Server started on port " << port << std::endl;
    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket != INVALID_SOCKET) {
            threads.emplace_back([clientSocket]() {
                ClientHandler handler(clientSocket);
                handler.handle();
                });
        }
    }
}

void Server::stop() {
    closesocket(listenSocket);
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
}
