#include "Polynomial.h"
#include <stdio.h>
#include <math.h>

void printPolynomial(Polynomial *polynomial) {
  for (int i = 0; i < polynomial->numberOfTerms; i++) {
    if (polynomial->terms[i].coefficient > 0 && i > 0) {
      printf("+ ");
    }

    if (polynomial->terms[i].degree == 1) {
      printf("%dx ", polynomial->terms[i].coefficient);
    } else if (polynomial->terms[i].degree == 0) {
      printf("%d ", polynomial->terms[i].coefficient);
    } else {
      printf("%dx^%d ", polynomial->terms[i].coefficient, polynomial->terms[i].degree);
    }
  }
  printf("\n");
}

double fOf(Polynomial *polynomial, double x){
  double sum = 0;

  for (int i = 0; i < polynomial->numberOfTerms; i++) {
      sum += pow(x, polynomial->terms[i].degree) * polynomial->terms[i].coefficient;;
  }
  return sum;
}
