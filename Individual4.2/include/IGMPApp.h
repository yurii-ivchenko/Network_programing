#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

class IGMPApp {
public:
    IGMPApp(const std::string& groupIP, int port);
    ~IGMPApp();
    void receiveMessages();

private:
    SOCKET sock;
    ip_mreq mreq;
};
