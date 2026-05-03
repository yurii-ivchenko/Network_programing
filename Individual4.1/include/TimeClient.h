#pragma once
#include <winsock2.h>
#include <string>

class TimeClient {
public:
    TimeClient(const std::string& ip, int port);
    ~TimeClient();
    void requestTime();

private:
    SOCKET clientSocket;
    sockaddr_in serverAddr;
};
