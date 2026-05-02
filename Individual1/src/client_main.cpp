#include "NetworkBase.h"
#include <iostream>

void showMenu() {
    std::cout << "\n--- POLYNOMIAL NETWORK SERVICE ---" << std::endl;
    std::cout << "1. Calculate P(x) (Horner's Method)" << std::endl;
    std::cout << "2. Get Polynomial Order (n)" << std::endl;
    std::cout << "3. Get All Coefficients" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choice: ";
}

int main() {
    NetworkBase net;
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(55555);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << "[ERROR] Connection failed!" << std::endl;
        return -1;
    }

    int choice;
    while (true) {
        showMenu();
        if (!(std::cin >> choice)) break;
        if (choice == 0) break;

        if (choice == 1) {
            double x; std::cout << "Enter x: "; std::cin >> x;
            net.SendMessage(sock, "EVAL " + std::to_string(x));
            std::cout << "Result P(" << x << ") = " << net.ReceiveMessage(sock) << std::endl;
        }
        else if (choice == 2) {
            net.SendMessage(sock, "ORDER");
            std::cout << "Order n = " << net.ReceiveMessage(sock) << std::endl;
        }
        else if (choice == 3) {
            net.SendMessage(sock, "COEFFS");
            std::cout << "Coefficients: " << net.ReceiveMessage(sock) << std::endl;
        }
    }
    return 0;
}