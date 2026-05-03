#pragma once
#include <winsock2.h>
#include <string>

class TimeServer {
public:
    TimeServer(int port);
    ~TimeServer();
    void run();

private:
    SOCKET serverSocket;
    sockaddr_in serverAddr;
};
