#include "Server.h"
#include <iostream>

Server::Server(const Polynomial& p) : poly(p), running(true) {}

Server::~Server() {
    closesocket(serverSocket);
    WSACleanup();
}

bool Server::init(int port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    bind(serverSocket, (struct sockaddr*)&server, sizeof(server));
    listen(serverSocket, 3);
    return true;
}

void Server::run() {
    std::cout << "Server started...\n";
    sockaddr_in client;
    int c = sizeof(sockaddr_in);
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&client, &c);

    char buffer[1024];
    while (running) {
        int recv_size = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (recv_size <= 0) break;
        buffer[recv_size] = '\0';

        std::string cmd(buffer);
        std::string response;

        if (cmd[0] == 'x') {
            double x = atof(cmd.substr(2).c_str());
            response = std::to_string(poly.evaluate(x));
        }
        else if (cmd[0] == 'd') {
            response = std::to_string(poly.getDegree());
        }
        else if (cmd[0] == 'c') {
            for (double coeff : poly.getCoeffs()) response += std::to_string(coeff) + " ";
        }
        else if (cmd == "shutdown") {
            response = "Server shutting down...";
            running = false;
        }
        else {
            response = "Unknown command";
        }
        send(clientSocket, response.c_str(), response.size(), 0);
    }
}

void Server::shutdown() {
    running = false;
}

// Точка входу
int main() {
    std::vector<double> coeffs = { 1, -3, 2 }; // x^2 - 3x + 2
    Polynomial poly(2, coeffs);

    Server server(poly);
    if (server.init(8080)) {
        server.run();
    }
    return 0;
}
