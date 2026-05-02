#include "HornerServer.h"
#include <iostream>

int main() {
    SetConsoleTitleA("Parallel Horner Server");

    // Створюємо об'єкт сервера
    HornerServer server("HornerPipe");

    std::cout << "===============================" << std::endl;
    std::cout << "   HORNER POLYNOMIAL SERVER    " << std::endl;
    std::cout << "===============================" << std::endl;

    // Запускаємо сервер
    server.start();

    return 0;
}