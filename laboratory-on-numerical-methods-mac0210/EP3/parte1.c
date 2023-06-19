/*
NOME: Beatriz Viana Costa
NUSP: 13673214
*/
/*
PARTE 1: Computando trabalho
*/
#include <stdio.h>

/*Os pontos que estão tabelados no enunciado*/
long double pontos_x[] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0};
/*f(x) = F(x)*cos(theta(x))*/
long double valores_fx[] = {0.0000, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537};

long double evalWj(int j);
long double evalP7x(long double x);
long double simpsonsRule(int r);
long double trapezoidalRule(int r);

int main(){
    int r;
    /*Quantidade de intervalos*/
    printf("Digite a quantidade de subintervalos (r): ");
    scanf("%d", &r);

    printf("O trabalho computado por meio da regra de Simpson composto: %Lf\n", simpsonsRule(r));
    printf("O trabalho computado por meio da regra do trapézio composto: %Lf\n", trapezoidalRule(r));

    return 0;
}

long double evalWj(int j){
    long double divisor = 1;
    int i;

    for(i=0; i<7; i++){
        if(i != j){
            divisor *= (pontos_x[j] - pontos_x[i]);
        }
    }

    return(1/divisor);
}

/*Calcula o polínômio interpolante de Lagrange*/
long double evalP7x(long double x){
    int i, j;
    long double psiX = 1;
    long double p7x = 0;
    long double aux = 0;

    /*Se o x dado como parâmetro tem um f(x) já tabelado -> evita divisão por 0*/
    for(i=0; i<7; i++){
        if(x == pontos_x[i]) 
            return valores_fx[i];
    }


    for(j=0; j<7; j++){
        psiX *= (x-pontos_x[j]);
        aux += (evalWj(j)*valores_fx[j])/(x-pontos_x[j]); 
    }

    p7x = psiX*aux;

    return p7x;
}

/* Regra de Simpson composto*/
long double simpsonsRule(int r){
    int i;
    long double h;
    long double value = 0;

    /* O método tem que ser aplicado com os subintervalos em pares*/
    if(r % 2 != 0)
        r++;
        /* Aumentar o subintervalo aumenta a precisão do método*/

    h = (long double)30/r;

    for(i=1; i<r/2; i++){
        value += 2*evalP7x(h*2*i) + 4*evalP7x((h*2*i)-1);
    }

    value += 4*evalP7x((h*2*(r/2))-1) + evalP7x(0.0) + evalP7x(30.0);

    value *= (long double)h/3;

    return value;
}

/* Regra do trapézio composto*/
long double trapezoidalRule(int r){
    int i;
    long double h = (long double)30/r;
    long double value = 0;

    /* 2*\sum_{i=1}^{i=r-1} f(t_i)*/
    for(i=1; i<r; i++){
        value += 2 * evalP7x(h*i);
    }

    value += evalP7x(0.0) + evalP7x(30.0);
    value *= (long double)h/2;

    return value;
}
