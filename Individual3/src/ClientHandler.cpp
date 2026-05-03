#include "ClientHandler.h"
#include "Polynom.h"
#include <iostream>

ClientHandler::ClientHandler(SOCKET socket) : clientSocket(socket) {}

void ClientHandler::handle() {
    char buffer[512];
    int result;
    do {
        result = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (result > 0) {
            std::string msg(buffer, result);
            std::cout << "[LOG] Received request: " << msg << std::endl;
            std::string response = Polynom::calculate(msg);
            std::cout << "[LOG] Response: " << response << std::endl;
            send(clientSocket, response.c_str(), response.size(), 0);
        }
    } while (result > 0);
    closesocket(clientSocket);
}
