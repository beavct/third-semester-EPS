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
    long double ponto = 7.7;
    /*Quantidade de intervalos*/
    int r = 5;

    //printf("%lf\n", evalP7x(ponto));

    return 0;
}

long double evalWj(int j){
    long double divisor = 1;

    for(int i=0; i<7; i++){
        if(i != j){
            divisor *= (pontos_x[j] - pontos_x[i]);
        }
    }

    return(1/divisor);
}

/*Calcula o polínômio interpolante de Lagrange*/
long double evalP7x(long double x){
    /*Se o x dado como parâmetro tem um f(x) já tabelado -> evita divisão por 0*/
    for(int i=0; i<7; i++){
        if(x == pontos_x[i]) 
            return valores_fx[i];
    }

    long double phiX = 1;
    long double p7x = 0;
    long double aux = 0;

    for(int j=0; j<7; j++){
        phiX *= (x-pontos_x[j]);
        aux += (evalWj(j)*valores_fx[j])/(x-pontos_x[j]); 
    }

    p7x = phiX*aux;

    return p7x;
}

/* Regra de Simpson composto*/
long double simpsonsRule(int r){
    /* O método tem que ser aplicado com os subintervalos em pares*/
    if(r % 2 != 0)
        /* Aumentar o subintervalo aumenta a precisão do método*/
        r++;

    int h = 30/r;
    long double value = 0;

    for(int i=1; i<r/2; i++){
        value += 2*evalP7x(h*2*i) + 4*evalP7x((h*2*i)-1);
    }

    value += 4*evalP7x((h*2*(r/2))-1) + evalP7x(0.0) + evalP7x(30.0);

    value *= h/3;

    return value;
}

/* Regra do trapézio composto*/
long double trapezoidalRule(int r){

    int h = 30/r;
    long double value = 0;

    /* 2*\sum_{i=1}^{i=r-1} f(t_i)*/
    for(int i=1; i<r; i++){
        value += evalP7x(h*i);
    }

    value *= 2;
    value += evalP7x(0.0) + evalP7x(30.0);
    value *= h/2;

    return value;
}
