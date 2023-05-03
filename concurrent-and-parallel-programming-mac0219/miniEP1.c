#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int N = 10000000;
    int i;
    int acertos = 0;
    float x, y;

    srand(time(0));

    for(i = 0; i < N; i++) {
        x = (float)rand()/RAND_MAX;
        y = (float)rand()/RAND_MAX;

        if (x*x + y*y <= 1.0)
            acertos++;
    }

    printf("%f\n", 4 * (float)acertos/N);

    return 0;
}