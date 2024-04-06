#include "Polynomial.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    Polynomial *polynomial = malloc(sizeof(Polynomial));
    polynomial->terms = malloc(MAX_NUM_OF_TERMS * sizeof(Term));

    int i = 0;
    int highestDegree = 0;
    printf("Insert the terms of a continuous polynomial\n");
    while (1) {
        int coefficient = 1;
        int degree = 0;

        printf("Coefficient: ");
        scanf("%d", &coefficient);
        printf("Degree: ");
        scanf("%d*c", &degree);

        if(degree > highestDegree){
            highestDegree = degree;
        }

        Term term;
        term.coefficient = coefficient;
        term.degree = degree;

        polynomial->terms[i] = term;

        printf("Add more terms? (y/n) ");
        char response;

        scanf(" %c", &response);

        if (response != 'y') {
            break;
        }
        i++;
    }
    polynomial->numberOfTerms = i + 1;
    printPolynomial(polynomial);

    printf("Is this your polynomial? (y/n) ");
    char response;
    scanf(" %c", &response);
    if (response != 'y') {
        main();
    }
    polynomial->degree = highestDegree;
    printf("highestDegree: %d\n", polynomial->degree);

    double res = fOf(polynomial, 2);
    printf("%f", res);

    return 0;
}
