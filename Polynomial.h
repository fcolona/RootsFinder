#define MAX_NUM_OF_TERMS 5

typedef struct Term {
	int coefficient;
	int degree;
	//if the degree is zero, then it is an independent term
} Term;

void printPolynomial(Term *polynomial, int numberOfTerms);
double fOf(Term* polynomial, double x, int numberOfTerms);