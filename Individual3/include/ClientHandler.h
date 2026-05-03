#pragma once
#include <winsock2.h>
#include <string>

class ClientHandler {
private:
    SOCKET clientSocket;
public:
    ClientHandler(SOCKET socket);
    void handle();
};
