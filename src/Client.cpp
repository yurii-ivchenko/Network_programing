#include "Client.h"
#include <iostream>

Client::Client() : running(true) {}

Client::~Client() {
    closesocket(sock);
    WSACleanup();
}

bool Client::connectToServer(const std::string& ip, int port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed\n";
        return false;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        return false;
    }

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_port = htons(port);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        return false;
    }

    return true;
}

void Client::run() {
    char buffer[1024];

    std::cout << "=== Client CLI ===\n";
    std::cout << "Command list:\n";
    std::cout << "  x <value>   - value polinom x\n";
    std::cout << "  d           - degree\n";
    std::cout << "  c           - coefficient\n";
    std::cout << "  shutdown    - shutting down server and client\n";
    std::cout << "  exit        - close client\n";
    std::cout << "==================\n";

    while (running) {
        std::cout << "\nPrint command: ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "exit") {
            running = false;
            std::cout << "Client shutting down...\n";
            break;
        }

        send(sock, cmd.c_str(), cmd.size(), 0);
        int recv_size = recv(sock, buffer, sizeof(buffer), 0);
        if (recv_size > 0) {
            buffer[recv_size] = '\0';
            std::cout << "Answer server: " << buffer << "\n";
            if (std::string(buffer).find("shutting down") != std::string::npos) {
                running = false;
            }
        }
    }
}

int main() {
    Client client;
    if (client.connectToServer("196.168.100.1", 8080)) {
        client.run();
    }
    return 0;
}
