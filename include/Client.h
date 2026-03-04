#pragma once
#include <winsock2.h>
#include <string>

class Client {
private:
    SOCKET sock;
    bool running;

public:
    Client();
    ~Client();

    bool connectToServer(const std::string& ip, int port);
    void run();
};
