#include "TimeClient.h"
#include <iostream>   

int main() {
    try {
        TimeClient client("192.168.0.249", 9090);

        while (true) {
            std::cout << "Press ENTER to request Unix time (or type 'exit' to quit): ";
            std::string input;
            std::getline(std::cin, input);

            if (input == "exit") {
                break;
            }

            client.requestTime();
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
