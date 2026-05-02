#include "NetworkBase.h"
#include "PolynomialLogic.h"
#include <iostream>

int main() {
    NetworkBase net;
    PolynomialLogic poly({ 2.0, -3.5, 1.0, 5.0 });

    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(55555);

    bind(listenSock, (sockaddr*)&addr, sizeof(addr));
    listen(listenSock, SOMAXCONN);

    std::cout << "[SERVER] Waiting for client connection..." << std::endl;
    SOCKET clientSock = accept(listenSock, NULL, NULL);
    std::cout << "[SERVER] Client connected!" << std::endl;

    while (true) {
        std::string req = net.ReceiveMessage(clientSock);
        if (req.empty() || req == "EXIT") break;

        std::cout << "[LOG] Request: " << req << std::endl;

        if (req.find("EVAL") == 0) {
            double x = std::stod(req.substr(5));
            net.SendMessage(clientSock, std::to_string(poly.calculateHorner(x)));
        }
        else if (req == "ORDER") {
            net.SendMessage(clientSock, std::to_string(poly.getOrder()));
        }
        else if (req == "COEFFS") {
            net.SendMessage(clientSock, poly.getCoeffsString());
        }
    }
    closesocket(clientSock);
    return 0;
}