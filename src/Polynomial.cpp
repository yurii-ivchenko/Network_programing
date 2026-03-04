#include "Polynomial.h"

Polynomial::Polynomial(int degree, const std::vector<double>& coeffs)
    : degree(degree), coeffs(coeffs) {
}

double Polynomial::evaluate(double x) const {
    double result = coeffs[0];
    for (int i = 1; i <= degree; i++) {
        result = result * x + coeffs[i];
    }
    return result;
}

int Polynomial::getDegree() const {
    return degree;
}

std::vector<double> Polynomial::getCoeffs() const {
    return coeffs;
}
