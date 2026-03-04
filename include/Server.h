#pragma once
#include "Polynomial.h"
#include <winsock2.h>
#include <string>

class Server {
private:
    SOCKET serverSocket;
    Polynomial poly;
    bool running;

public:
    Server(const Polynomial& p);
    ~Server();

    bool init(int port);
    void run();
    void shutdown();
};
