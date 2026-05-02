#pragma once
#include <winsock2.h>
#include <string>
#include <iostream>

class NetworkBase {
protected:
    SOCKET m_socket;
    sockaddr_in m_addr;
public:
    NetworkBase();
    virtual ~NetworkBase();
    void Close();
    bool SendMessage(SOCKET target, const std::string& msg);
    std::string ReceiveMessage(SOCKET target);
};