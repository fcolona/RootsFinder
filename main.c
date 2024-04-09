#include "polynomial.h"
#include <float.h>
#include <pthread.h>
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
    polynomial->roots = malloc(sizeof(typeof(double)) * polynomial->degree);
    pthread_mutex_init(&polynomial->lock, NULL);

    //Fill roots array with junk value
    //In order to further verify if an array element has not been initialized
    for (int i = 0 ; i < polynomial->degree; i++) {
        polynomial->roots[i] = DBL_MAX;
    }

    findRoots(polynomial);
    for (int i = 0; i < polynomial->degree; i++) {
        printf("roots[%d]: %f\n", i, polynomial->roots[i]);
    }

    return 0;
}
