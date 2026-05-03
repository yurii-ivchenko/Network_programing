#include <winsock2.h>
#include <iostream>
#include <string>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    std::string ip;
    std::cout << "Enter server IP address: ";
    std::getline(std::cin, ip);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server " << ip << ". Type 'exit' to quit." << std::endl;

    std::string input;
    char buffer[512];
    while (true) {
        std::cout << "Enter command (POLY x c0 c1 ... cn): ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        send(sock, input.c_str(), input.size(), 0);

        int result = recv(sock, buffer, sizeof(buffer), 0);
        if (result > 0) {
            std::string response(buffer, result);
            std::cout << "Server response: " << response << std::endl;
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
