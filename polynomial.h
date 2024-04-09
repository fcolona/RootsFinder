#include <pthread.h>
#define MAX_NUM_OF_TERMS 5
#define DECIMAL_ROOTS_PRECISION 9

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
double* refineInterval(Polynomial *polynomial, double* interval);
