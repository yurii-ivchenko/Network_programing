#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct {
    int degree;
    double *coeffs;
} Polynomial;

Polynomial* create_polynomial(int degree, double* coeffs);
void free_polynomial(Polynomial* poly);

double evaluate_polynomial(Polynomial* poly, double x);
int get_degree(Polynomial* poly);
double* get_coeffs(Polynomial* poly);

#endif
