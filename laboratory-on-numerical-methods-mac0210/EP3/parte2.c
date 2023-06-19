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

#define f(x) sin(x)
#define g(x) pow(x,3)
#define h(x) exp(-x)

double monteCarloUni(int a, int b, unsigned long int n, int op);
double monteCarloMulti(unsigned long int n);

int main(){
    unsigned long int n;

    printf("Digite a quantidade de variáveis aleatórias (n): ");
    scanf("%lud", &n);

    printf("Aproximação da integral de sen(x) calculada de 0 à 1: %f\n", monteCarloUni(0, 1, n, 1));
    printf("Aproximação da integral de x à terceira calculada de 3 à 7: %f\n", monteCarloUni(3, 7, n, 2));
    printf("Aproximação da exponencial elevada à -x calculada de 0 à infinito: %f\n", monteCarloUni(0, 1, n, 3));
    printf("Aproximação de Pi: %f\n", monteCarloMulti(n));

    return 0;
}

double monteCarloUni(int a, int b, unsigned long int n, int op){
    double aprox = 0;
    double x;
    long unsigned int i;

    srand(time(0));

    for(i = 0; i < n; i++) {
        x = (double)rand()/RAND_MAX;

        if(op == 1)
            aprox += f(x);
        else if(op == 2)
            aprox += g(a + x * (b-a));
        else /*op == 3*/
            aprox += h(x) + h(1);

    }

    return (double)aprox/n * (b-a);
}

/* Está calculando para Pi - OK */
double monteCarloMulti(unsigned long int n){
    double aprox = 0;
    double x, y;
    long unsigned int i;

    srand(time(0));

    for(i = 0; i < n; i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;

        if (x*x + y*y <= 1.0)
            aprox++;
    }

    aprox = 4 * (double)aprox/n;

    return aprox;
}
