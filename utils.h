#ifndef UTILS_H
#define UTILS_H

#include "polynomial.h"

typedef struct PolynomialAndInterval {
    Polynomial *polynomial;
    double* interval;
} PolynomialAndInterval ;

double module(double x);
#endif
