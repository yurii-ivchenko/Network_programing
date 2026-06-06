#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class IGMPServer {
public:
    IGMPServer(const std::string& groupIP, int port);
    ~IGMPServer();
    void sendMessage(const std::string& msg);

private:
    SOCKET sock;
    sockaddr_in groupAddr;
};
