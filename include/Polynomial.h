#pragma once
#include <vector>

class Polynomial {
private:
    int degree;
    std::vector<double> coeffs;

public:
    
    Polynomial(int degree, const std::vector<double>& coeffs);

    double evaluate(double x) const;

    int getDegree() const;

    std::vector<double> getCoeffs() const;
};
