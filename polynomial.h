#define MAX_NUM_OF_TERMS 5

typedef struct Term {
    int coefficient;
	int degree;
	//if the degree is zero, then it is an independent term
} Term;

typedef struct Polynomial {
    int degree;
	int numberOfTerms;
	Term* terms;
} Polynomial;

void printPolynomial(Polynomial *polynomial);
double fOf(Polynomial *polynomial, double x);
double findRoot(Polynomial *polynomial);
double* refineInterval(Polynomial *polynomial, double* interval);
