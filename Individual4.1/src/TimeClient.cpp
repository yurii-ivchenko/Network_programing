#include "TimeClient.h"
#include <iostream>

TimeClient::TimeClient(const std::string& ip, int port) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        throw std::runtime_error("Failed to create socket");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
}

TimeClient::~TimeClient() {
    closesocket(clientSocket);
    WSACleanup();
}

void TimeClient::requestTime() {
    std::string request = "time";
    sendto(clientSocket, request.c_str(), request.size(), 0,
        (sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[256];
    int serverAddrSize = sizeof(serverAddr);
    int bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer), 0,
        (sockaddr*)&serverAddr, &serverAddrSize);
    if (bytesReceived != SOCKET_ERROR) {
        buffer[bytesReceived] = '\0';
        std::cout << "Unix time from server: " << buffer << std::endl;
    }
}
