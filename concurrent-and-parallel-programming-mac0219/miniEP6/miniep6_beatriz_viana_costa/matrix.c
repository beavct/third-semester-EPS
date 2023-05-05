#include "matrix.h"

#include <stdlib.h>

/* Módulo de x*/
#define ABS(x) ((x > 0)? (x): -(x))


void matrix_fill_rand(int n, double *restrict _A)
{
    #define A(i, j) _A[n*(i) + (j)]
	int i, j;

	for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            A(i, j) = 10*(double) rand() / (double) RAND_MAX;

    #undef A
}

void matrix_dgemm_0(int n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    /* Macros para acessar os elementos das matrizes mais facilmente*/
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]
    int i, j, k;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            double sum = 0;
            for (k = 0; k < n; ++k)
                sum += A(i, k)*B(k, j);
            C(i, j) = sum;
        }
    

    /*for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%d ", C(i,j));
        printf("\n");
    }

    printf("FIM \n\n");*/


    #undef A
    #undef B
    #undef C
}

void matrix_dgemm_1(int n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]

    /* Código do mini EP 5 aqui */
        int i, j, k;

    for(k=0; k<n; k++){
        for(i=0; i<n; i++){
            for(j=0; j<n; j++){
                C(i,j)+=A(i, k) * B(k, j);
            }
        }
    }

    /*for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%d ", C(i,j));
        printf("\n");
    }

    printf("FIM \n\n");*/

    #undef A
    #undef B
    #undef C
}

void matrix_dgemm_2(int n, double *restrict _C, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]
    #define C(i, j) _C[n*(i) + (j)]

    /* Aqui você deve usar blocagem, em conjunto com a técnica que você
     * desenvolveu em dgemm_1. Espera-se que haja redução do tempo de execução
     * em relação a dgemm_1, embora não tão significativa do que aquela
     * observada entre dgemm_0 e dgemm_1.
     * Dependendo da sua máquina, a redução no tempo de execução pode ser de
     * 1 a 2 segundos, ou até metade do tempo de dgemm_1.
     */
    /* Código do mini EP 6 aqui */


    int i, j, k, ii, jj, kk, tamBloco;

    tamBloco = n/64 ;

    for (kk = 0; kk < n; kk+=tamBloco) {
        for (ii = 0; ii < n; ii+=tamBloco) {
            for (jj = 0; jj < n; jj+=tamBloco) {
                for (k = kk; k < kk+tamBloco && k < n; k++) {
                    for (i = ii; i < ii+tamBloco && i < n; i++) {
                        for (j = jj; j < jj+tamBloco && j < n; j++) {
                            C(i,j) += A(i,k)*B(k,j);
                        }
                    }
                }
            }
        }
    }

    /*for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%d ", C(i,j));
        printf("\n");
    }

    printf("FIM \n\n");*/

    #undef A
    #undef B
    #undef C
}


bool matrix_eq(int n, double *restrict _A, double *restrict _B)
{
    #define A(i, j) _A[n*(i) + (j)]
    #define B(i, j) _B[n*(i) + (j)]

    int i, j;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (ABS (A(i, j) - B(i, j)) > 1e-15)
                return false;

    return true;
    #undef A
    #undef B
}


bool matrix_which_dgemm(int algorithm, int n,  double *restrict _C,
                        double *restrict _A, double *restrict _B)
{
    bool ret;
    switch(algorithm)
    {
        case 0:
            matrix_dgemm_0(n, _C, _A, _B);
            ret = true;
            break;

        case 1:
            matrix_dgemm_1(n, _C, _A, _B);
            ret = true;
            break;

        case 2:
            matrix_dgemm_2(n, _C, _A, _B);
            ret = true;
            break;

        default:
            ret = false;
    }
    return ret;
}

