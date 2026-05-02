#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

void showMenu() {
    std::cout << "\n=== HORNER CLI CLIENT ===" << std::endl;
    std::cout << "1. Calculate Polynomial" << std::endl;
    std::cout << "2. About Algorithm" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "choice> ";
}

int main() {
    int choice = 0;
    while (true) {
        showMenu();
        std::cin >> choice;

        if (choice == 3) break;
        if (choice == 2) {
            std::cout << "Horner's method reduces the number of multiplications for polynomials." << std::endl;
            continue;
        }

        HANDLE hPipe = CreateFileA("\\\\.\\pipe\\HornerPipe",
            GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Error: Server not found!" << std::endl;
            continue;
        }

        std::cout << "Enter X and then coefficients (space separated): ";
        std::string data;
        std::cin.ignore();
        std::getline(std::cin, data);

        DWORD written, read;
        WriteFile(hPipe, data.c_str(), (DWORD)data.length(), &written, NULL);

        char buffer[512];
        if (ReadFile(hPipe, buffer, 511, &read, NULL)) {
            buffer[read] = '\0';
            std::cout << "RESULT: " << buffer << std::endl;
        }
        CloseHandle(hPipe);
    }
    return 0;
}