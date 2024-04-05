#include "Polynomial.h"
#include <stdio.h>
#include <math.h>

void printPolynomial(Term *polynomial, int numberOfTerms) {
  for (int i = 0; i < numberOfTerms; i++) {
    if (polynomial[i].coefficient > 0 && i > 0) {
      printf("+ ");
    }

    if (polynomial[i].degree == 1) {
      printf("%dx ", polynomial[i].coefficient);
    } else if (polynomial[i].degree == 0) {
      printf("%d ", polynomial[i].coefficient);
    } else {
      printf("%dx^%d ", polynomial[i].coefficient, polynomial[i].degree);
    }
  }
  printf("\n");
}

double fOf(Term *polynomial, double x, int numberOfTerms){
  double sum = 0;

  for (int i = 0; i < numberOfTerms; i++) {
      sum += pow(x, polynomial[i].degree) * polynomial[i].coefficient;;
  }
  return sum;
}