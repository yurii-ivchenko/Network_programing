#include "polynomial.h"
#include <stdlib.h>

Polynomial* create_polynomial(int degree, double* coeffs) {
    Polynomial* poly = (Polynomial*)malloc(sizeof(Polynomial));
    poly->degree = degree;
    poly->coeffs = (double*)malloc((degree+1) * sizeof(double));
    for(int i=0; i<=degree; i++) {
        poly->coeffs[i] = coeffs[i];
    }
    return poly;
}

void free_polynomial(Polynomial* poly) {
    if(poly) {
        free(poly->coeffs);
        free(poly);
    }
}

double evaluate_polynomial(Polynomial* poly, double x) {
    double result = poly->coeffs[0];
    for(int i=1; i<=poly->degree; i++) {
        result = result * x + poly->coeffs[i];
    }
    return result;
}

int get_degree(Polynomial* poly) {
    return poly->degree;
}

double* get_coeffs(Polynomial* poly) {
    return poly->coeffs;
}
