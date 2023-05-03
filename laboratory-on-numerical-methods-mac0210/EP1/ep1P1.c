#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* gcc -ansi -Wall -pedantic ep1P1.c -lm
    ./a.out
*/

#define f(x) exp(x)-2*pow(x, 2)
#define g1(x) -sqrt(exp(x)/2)
#define g2(x) log(2*pow(x,2))
#define g3(x) sqrt(exp(x)/2)

#define xtol 1e-8

void avaliaG(double x0){
    double x1;
    int i = 1;

    if(x0 <= 2 && x0 >= 0){
        x1 = g1(x0);
        while(fabs(x0-x1)>xtol){
            x0 = x1;
            x1 = g1(x0);
            i++;
        }
    }
    else if(x0 > 2){
        x1 = g2(x0);
        while(fabs(x0-x1)>xtol){
            x0 = x1;
            x1 = g2(x0);
            i++;
        }
    }
    else if(x0 < 0){
        x1 = g3(x0);
        while(fabs(x0-x1)>xtol){
            x0 = x1;
            x1 = g3(x0);
            i++;
        }
    }

    printf("O método convergiu para a raiz %f em %d passos.\n", x1, i);
}

int main(){
    double x0;

    printf("Digite o ponto inicial x0: ");
    scanf("%lf", &x0);

    avaliaG(x0);

    return 0;
}