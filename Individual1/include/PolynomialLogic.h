#pragma once
#include <vector>
#include <string>

class PolynomialLogic {
private:
    std::vector<double> m_coeffs; // a0, a1, ... an
public:
    PolynomialLogic(std::vector<double> coeffs);
    double calculateHorner(double x);
    int getOrder() const;
    std::string getCoeffsString() const;
};