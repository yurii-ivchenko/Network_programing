#include "TimeServer.h"
#include <iostream>

int main() {
    try {
        TimeServer server(9090);
        server.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
