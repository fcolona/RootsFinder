#include "polynomial.h"
#include "utils.h"
#include <float.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>

int continueToSearchFlag = 1;

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
    }
    return sum;
}

double* refineInterval(Polynomial *polynomial, double* interval){
    double middle = (interval[0] + interval[1])/2;    

    double fOfMiddle = fOf(polynomial, middle);
    if(fOfMiddle == 0){
        interval[0] = middle;
        interval[1] = middle;

        return interval;
    }
    else if(fOfMiddle < 0){
        if(fOf(polynomial, interval[0]) < 0){
            interval[0] = middle;
            return interval;
        }
        interval[1] = middle;
        return interval;
    }
    else if(fOf(polynomial, interval[0]) > 0){
        interval[0] = middle;
        return interval;
    }
    interval[1] = middle;
    return interval;
}

void* searchLeft(void *polynomialArg){
    Polynomial* polynomial = (Polynomial*) polynomialArg;

    double fOfZero = fOf(polynomial, 0);

    //last fOf(x) that was positive/negative
    double lastfOfX = fOfZero;

    //last x that was positive/negative
    int lastX = 0;

    int x = 0;

    while(1){
        if(continueToSearchFlag != 1){
            return NULL;
        }

        double fOfX = fOf(polynomial, x);
        if(fOfX == 0){
            pthread_mutex_lock(&polynomial->lock);

            int i = 0;
            while (i < polynomial->degree) {
                if(polynomial->roots[i] == DBL_MAX){
                    polynomial->roots[i] = x;
                    break;
                };
                i++;
            }
            pthread_mutex_unlock(&polynomial->lock);

            int indexOfLastRootFound = i + 1;

            //Checks if all roots have been found;
            if(indexOfLastRootFound == polynomial->degree){
                continueToSearchFlag = 0;
                return NULL;
            }
        }

        //There was a change of sign
        if((lastfOfX < 0 && fOfX > 0) || (lastfOfX  > 0 && fOfX < 0)){
             //The root is in this interval
            printf("beginning: %d, end: %d\n", lastX, x);

            double interval[2];
            interval[0] = lastX;
            interval[1] = x;

            int i = 0;
            while(i < DECIMAL_ROOTS_PRECISION ){
                refineInterval(polynomial, interval);
                //printf("beginning: %f, end: %f\n", interval[0], interval[1]);
                i++;
            }
            for (int i = 0; i < polynomial->degree; i++) {
                //It means that the array at position i does not have a meaningful value
                if(polynomial->roots[i] == DBL_MAX){
                    polynomial->roots[i] = interval[0];
                    break;
                };
            }
            break;
        }
        lastfOfX = fOfX;
        lastX = x;
        x--;
    }
    return NULL;
}


void* searchRight(void *polynomialArg){
    if(continueToSearchFlag != 1){
        return NULL;
    }

    Polynomial* polynomial = (Polynomial*) polynomialArg;

    double fOfZero = fOf(polynomial, 0);

    //last fOf(x) that was positive/negative
    double lastfOfX = fOfZero;

    //last x that was positive/negative
    int lastX = 0;
    int x = 1;

    while(1){
        double fOfX = fOf(polynomial, x);
        if(fOfX == 0){
            pthread_mutex_lock(&polynomial->lock);

            int i = 0;
            while (i < polynomial->degree) {
                if(polynomial->roots[i] == DBL_MAX){
                    polynomial->roots[i] = x;
                    break;
                };
                i++;
            }
            pthread_mutex_unlock(&polynomial->lock);

            int indexOfLastRootFound = i + 1;

            //Checks if all roots have been found;
            if(indexOfLastRootFound == polynomial->degree){
                continueToSearchFlag = 0;
                return NULL;
            }
        }

        //There was a change of sign
        if((lastfOfX < 0 && fOfX > 0) || (lastfOfX  > 0 && fOfX < 0)){
            //The root is in this interval
            //printf("beginning: %d, end: %d\n", lastX, x);

            double interval[2];
            interval[0] = lastX;
            interval[1] = x;

            int i = 0;
            while(i < DECIMAL_ROOTS_PRECISION ){
                refineInterval(polynomial, interval);
                //printf("beginning: %f, end: %f\n", interval[0], interval[1]);
                i++;
            }
            for (int i = 0; i < polynomial->degree; i++) {
                //It means that the array at position i does not have a meaningful value
                if(polynomial->roots[i] == DBL_MAX){
                    polynomial->roots[i] = interval[0];
                    break;
                };
            }
            break;
        }
        lastfOfX = fOfX;
        lastX = x;
        x++;
    }
    return NULL;
}

void findRoots(Polynomial *polynomial){
    pthread_t threadLeft;
    pthread_t threadRight;

    pthread_create(&threadLeft, NULL, searchLeft, (void*)polynomial);
    pthread_create(&threadRight, NULL, searchRight, (void*)polynomial);

    pthread_join(threadLeft, NULL);
    pthread_join(threadRight, NULL);
}

