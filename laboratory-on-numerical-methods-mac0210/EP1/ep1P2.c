#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

/* gcc -ansi -Wall -pedantic ep1P2.c -lm
    ./a.out

    gnuplot
    set terminal png size (1200, 800)
    set output "teste.png"
    plot "output.txt" with image pixel
*/
#define f(x) 17*cpow(x,9)+8*cpow(x,5)+12*cpow(x,2)+21*x-80
#define Df(x) 17*9*cpow(x,8)+8*5*cpow(x,4)+12*2*x+21

#define xtol 1e-8

typedef struct{
    double complex *raizes;
    int *cores;
    int tam;
    int ind; /*Guarda a próxima posição vazia*/
}info;


double complex evalf(double complex x){
    return f(x);
}

double complex evalDf(double complex x){
    return Df(x);
}

double complex newton(double complex x0){
    double complex x1;
    int i=1;

    x1 = x0 - (evalf(x0)/evalDf(x0));
    while(cabs(x1-x0) > xtol){
        x0 = x1;
        x1 = x0 - (evalf(x0)/evalDf(x0));
        i++;
    }
    /*printf("O número complexo é: %f%+fi\n", creal(x1), cimag(x1));*/
    return x1;
}

info *resize(info *velho){
    int i;

    info *novo = malloc(sizeof(info*));
    novo->raizes = malloc(sizeof(double complex)*2*velho->tam);
    novo->cores = malloc(sizeof(int)*2*velho->tam);
    novo->tam = 2*velho->tam;
    novo->ind = velho->ind;

    for(i=1; i<velho->tam; i++){
        novo->raizes[i] = velho->raizes[i];
        novo->cores[i] = velho->cores[i]; 
    }
    return novo;
}

void newton_basins(double complex l, double complex u, int p) {
    FILE *output;
    int **cores;
    double *x, *y;
    double complex **z;
    info *info;
    int i, j, k, flag=0;
    double complex x0, raiz;

    /*Malloca os arrays que serão utilizados*/
    cores = malloc(sizeof(int*)*p);
    for(i=0; i<p; i++)
        cores[i] = malloc(sizeof(int)*p);
    
    x = malloc(sizeof(double)*p);
    y = malloc(sizeof(double)*p);

    z = malloc(sizeof(double complex*)*p);
    for(i=0; i<p; i++)
        z[i]= malloc(sizeof(double complex)*p);

    /*malloca o vetor que irá guardar as informações das raízes*/
    info = malloc(sizeof(info));
    info->raizes = malloc(sizeof(double complex)*2);
    info->cores = malloc(sizeof(int)*2);
    info->tam = 2;
    info->ind = 0; 

    /*Pontos dos complexos a partir do l, u e p dados*/
    for (i = 0; i < p; i++) {
        x[i] = creal(l) + i * (creal(u)-creal(l)) / (p-1);
        y[i] = cimag(l) + i * (cimag(u)-cimag(l)) / (p-1);
    }
    for (i = 0; i < p; i++) {
        for (j = 0; j < p; j++) {
            z[i][j] = x[i] + I * y[j];
        }
    }

    for(i=0; i<p; i++){
        for(j=0; j<p; j++){

            x0 = z[i][j];
            raiz = newton(x0);

            if(raiz != raiz){
                cores[i][j] = 0; /*para tratar o caso de nan*/
                flag=1;
            }

            for(k=0; k<info->ind && !flag;k++){
                if(cabs(raiz - info->raizes[k]) < xtol){
                    cores[i][j] = info->cores[k];
                    flag=1;
                }
            }

            if(!flag){
                if(info->ind == info->tam)
                    info = resize(info);
                info->raizes[info->ind] = raiz;
                info->cores[info->ind] = info->ind;

                cores[i][j] = info->ind;
                info->ind++;
            }
            flag=0;
        }
    }

    /*Coloca os dados no arquivo .txt para plotar a imagem*/
    output = fopen("output.txt", "w");
    for (i = 0; i < p; i++) {
        for (j = 0; j < p; j++) {
            fprintf(output, "%f %f %d\n", x[i], y[j], cores[i][j]);
        }
        fprintf(output, "\n");
    }
    fclose(output);

    /*Libera o espaço dos arrays mallocados*/
    free(info->raizes);
    free(info->cores);
    free(info);

    for(i=0; i<p; i++){
        free(cores[i]);
        free(z[i]);
    }
    free(cores);
    free(x);
    free(y);
    free(z);

}


int main(){
    int p=1000;
    double complex l = -50.0 - 50.0*I, u = 50.0 + 50.0*I; 

    newton_basins(l, u, p);

    return 0;
}