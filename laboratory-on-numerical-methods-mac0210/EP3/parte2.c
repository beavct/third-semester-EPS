/*
NOME: Beatriz Viana Costa
NUSP: 13673214
*/
/*
PARTE 2: INtegração por Monte Carlo
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Para sin(x) está funcionando*/
#define f(x) pow(x,3)

double monteCarloUni(int a, int b, unsigned long int n);
double monteCarloMulti(int a, int b, unsigned long int n);

int main(){

    printf("%lf\n", monteCarloMulti(3, 7, 10000000));

    return 0;
}

double monteCarloUni(int a, int b, unsigned long int n){
    double aprox = 0;
    double x, y;

    srand(time(0));

    for(long unsigned int i = 0; i < n; i++) {
        x = (double)rand()/RAND_MAX;

        aprox += f(x);
    }

    return aprox/n;

}

/* Está calculando para Pi - OK */
double monteCarloMulti(int a, int b, unsigned long int n){
    double aprox = 0;
    double x, y;

    srand(time(0));

    for(long unsigned int i = 0; i < n; i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;

        if (x*x + y*y <= 1.0)
            aprox++;
    }

    //printf("%f\n", 4 * (float)aprox/n);

    aprox = 4 * (double)aprox/n;

    return aprox;
}
