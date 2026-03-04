#include "Client.h"
#include <iostream>

Client::Client() : running(true) {}

Client::~Client() {
    closesocket(sock);
    WSACleanup();
}

bool Client::connectToServer(const std::string& ip, int port) {
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0) return false;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_port = htons(port);

    return connect(sock, (struct sockaddr*)&server, sizeof(server)) == 0;
}

void Client::run() {
    char buffer[1024];

    std::cout << "=== Client CLI ===\n";
    std::cout << "Commands list:\n";
    std::cout << "  x <value>   - polinom value x\n";
    std::cout << "  d           - degree\n";
    std::cout << "  c           - coefficient\n";
    std::cout << "  shutdown    - server shudown\n";
    std::cout << "  exit        - client close\n";
    std::cout << "==================\n";

    while(running) {
        std::cout << "\nPrint your command: ";
        std::string cmd;
        std::getline(std::cin, cmd);

        if(cmd == "exit") {
            running = false;
            std::cout << "Client shutdown...\n";
            break;
        }

        send(sock, cmd.c_str(), cmd.size(), 0);
        int recv_size = recv(sock, buffer, sizeof(buffer), 0);
        if(recv_size > 0) {
            buffer[recv_size] = '\0';
            std::cout << "Answer server: " << buffer << "\n";
            if(std::string(buffer).find("shutting down") != std::string::npos) {
                running = false;
            }
        }
    }
}
