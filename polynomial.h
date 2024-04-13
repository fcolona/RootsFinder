#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H 

#define MAX_NUM_OF_TERMS 5
#define DECIMAL_ROOTS_PRECISION 9


#include <pthread.h>
typedef struct Term {
    int coefficient;
	int degree;
	//if the degree is zero, then it is an independent term
} Term;

typedef struct Polynomial {
    int degree;
	int numberOfTerms;
	Term* terms;
    pthread_mutex_t lock;
    double *roots;
} Polynomial;

void printPolynomial(Polynomial *polynomial);
double fOf(Polynomial *polynomial, double x);
void findRoots(Polynomial *polynomial);
void* refineInterval(void *polynomialAndInterval);
#endif
