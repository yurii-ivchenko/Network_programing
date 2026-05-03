#include "Polynom.h"
#include <sstream>
#include <vector>

std::string Polynom::calculate(const std::string& command) {
    std::istringstream iss(command);
    std::string op;
    iss >> op;

    if (op == "POLY") {
        int x;
        iss >> x;
        std::vector<int> coeffs;
        int c;
        while (iss >> c) coeffs.push_back(c);

        if (coeffs.empty()) return "Error: No coefficients provided";

        long long result = coeffs[0];
        for (size_t i = 1; i < coeffs.size(); ++i) {
            result = result * x + coeffs[i];
        }
        return std::to_string(result);
    }

    return "Unknown command";
}
