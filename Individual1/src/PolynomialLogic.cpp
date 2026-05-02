#include "PolynomialLogic.h"
#include <sstream>

PolynomialLogic::PolynomialLogic(std::vector<double> coeffs) : m_coeffs(coeffs) {}

double PolynomialLogic::calculateHorner(double x) {
    double result = m_coeffs[0];
    for (size_t i = 1; i < m_coeffs.size(); ++i) {
        result = result * x + m_coeffs[i];
    }
    return result;
}

int PolynomialLogic::getOrder() const {
    return static_cast<int>(m_coeffs.size()) - 1;
}

std::string PolynomialLogic::getCoeffsString() const {
    std::stringstream ss;
    for (double c : m_coeffs) ss << c << " ";
    return ss.str();
}