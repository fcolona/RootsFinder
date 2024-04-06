#include "polynomial.h"
#include "utils.h"
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
        //If it is an independent term
        if(polynomial->terms[i].degree == 0){
            sum += polynomial->terms[i].coefficient;
            continue;
        }
        sum += (pow(x, polynomial->terms[i].degree) * polynomial->terms[i].coefficient);
        printf("patial sum: %f\n", sum);
    }
    return sum;
}

double findRoot(Polynomial *polynomial){

    double fOfNegativeOne = fOf(polynomial, -1);
    double fOfZero = fOf(polynomial, 0);
    double fOfOne = fOf(polynomial, 1);

    if(fOfNegativeOne == 0){
        return fOfNegativeOne;
    }
    else if(fOfZero == 0){
        return fOfZero;
    }
    else if(fOfOne == 0){
        return fOfOne;
    }

    if(module(fOfNegativeOne) < module(fOfOne)){
        //printf("Foi pro negativo\n");

        //last fOf(x) that was positive/negative
        double lastfOfX = fOfZero;

        //last x that was positive/negative
        int lastX = 0;

        int x = 1;
        while(1){
            double fOfX = fOf(polynomial, x);
            if(fOfX == 0){
                return x;
            }

            //There was a change of sign
            if(lastfOfX  < 0 && fOfX > 0){
                //The root is in this interval
                printf("beginning: %d, end: %d\n", lastX, x);
            }
            else if(lastfOfX  > 0 && fOfX < 0){
                //The root is in this interval
                printf("beginning: %d, end: %d\n", lastX, x);
            }

            lastfOfX = fOfX;
            lastX = x;
            x--;
        }
    }
    else if(module(fOfNegativeOne) > module(fOfOne)){

        //last fOf(x) that was positive/negative
        double lastfOfX = fOfZero;

        //last x that was positive/negative
        int lastX = 0;

        int x = 1;
        while(1){
            double fOfX = fOf(polynomial, x);
            if(fOfX == 0){
                return x;
            }

            //There was a change of sign
            if(lastfOfX < 0 && fOfX > 0){
                //The root is in this interval
                printf("beginning: %d, end: %d\n", lastX, x);
                break;
            }
            else if(lastfOfX > 0 && fOfX < 0){
                //The root is in this interval
                printf("beginning: %d, end: %d\n", lastX, x);
                break;
            }

            lastfOfX = fOfX;
            lastX = x;
            x++;
        }
    }

    return -1;
}
