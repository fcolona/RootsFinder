#include "Polynomial.h"
#include <stdio.h>

int main(void) {
  Term polynomial[MAX_NUM_OF_TERMS];

  int i = 0;
  while (1) {
    printf("Insert the terms of a continuous polynomial\n");
    
    int coefficient = 1;
    int degree = 0;

    printf("Coefficient: ");
    scanf("%d", &coefficient);
    printf("Degree: ");
    scanf("%d*c", &degree);

    Term term;
    term.coefficient = coefficient;
    term.degree = degree;

    polynomial[i] = term;

    printf("Add more terms? (y/n) ");
    char response;
    scanf(" %c", &response);

    if (response != 'y') {
      break;
    }
    i++;
  }
  printPolynomial(polynomial, i);

  printf("Is this your polynomial? (y/n) ");
  char response;
  scanf(" %c", &response);
  if (response != 'y') {
    main();
  }

  return 0;
}
