#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

// Macro utilizada pela ferramenta make para substituir @#@IF por
// K ifs encadeados. Não escreva @#@IF em outros lugares no código,
// exceto onde já estiver sendo utilizado
#define IF_GT_MAX if(t->arr[i] > max)

pthread_mutex_t lock; // lock para a variável global max
double max = -1; // valor máximo armazenado no vetor

// Uma tarefa (task) a ser executada por uma thread, contendo um
// ponteiro para a posição apropriada do vetor (arr), assim como o número
// de elementos a serem processados (size)
struct task {
        double *arr;
        int size;
};

// Imprime uma mensagem de erro e finaliza execução com código de retorno de erro
#define DIE(...) { \
        fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_FAILURE); \
}

// Uma função não-otimizada para cálculo do fatorial de n
int factorial(int n) {
        int ret = 1;
        for (int i = 2; i <= n; ++i)
                ret *= i;
        return ret;
}

// Função que realiza cálculos trabalhosos e sem sentido, cujo objetivo é
// apenas fazer as threads trabalharem por mais tempo para facilitar a observação
// dos efeitos de contenção. Divirtam-se, threads :)
// Obs: é possível que haja overflows ou NaNs nestas computações
double a_laborious_function(double x) {
        double a = atan(x) + cos(x);
        double dadx = (1./(pow(x+0.2, 2) + 1.)) - sin(x);
        double k = a + (dadx * pow(x, 12)) / (double)factorial(9);
        double s = 12.12 / (double)factorial(12) / factorial(11);
        k += (pow(x, 5) / (double)factorial(12)) * s;
        k -= sin(dadx) + 2 * M_PI * cos(dadx);
        return k > 0 ? k : -k;
}

// Função que recebe uma tarefa (task) t e realiza cálculos trabalhosos em t-size
// elementos em t->arr. Após o trabalho, verifica se o elemento atual é maior do que
// a variável global 'max' e, nesse caso, atualiza o valor de 'max' com o valor do elemento
void *thread_work(void *arg) {
        struct task *t = (struct task *)arg;

        for (int i = 0; i < t->size; ++i) {
                t->arr[i] = a_laborious_function(t->arr[i]);
                t->arr[i] = a_laborious_function(t->arr[i]);

                // proteção para possíveis NaNs ou overflows
                if(isnan(t->arr[i]) || isinf(t->arr[i]))
                        t->arr[i] = rand() / RAND_MAX;

                // Não modifique o comentário a seguir (linha 69). 
                // Ele será substituído em tempo de compilação de acordo 
                // com o valor do parâmetro IF do Makefile:

                //@#@IF
                {
                        pthread_mutex_lock(&lock);
                        if (t->arr[i] > max)
                                max = t->arr[i];
                        pthread_mutex_unlock(&lock);
                }

        }

        return NULL;
}

// Preenche o vetor V com valores pseudoaleatórios de doubles
void fill_array(double *V, int N) {
        srand(2382); // inicialização arbitrária
        for (int i = 0; i < N; ++i)
                V[i] = (double)rand() / RAND_MAX;
}

int main(int argc, char **argv)
{
        pthread_t *threads;
        unsigned num_threads;
        struct task *tasks;
        int N;
        double *V;
        struct timeval start, end;

        // Parsing dos argumentos da linha de comando
        if (argc != 3 || sscanf(argv[1], "%u", &num_threads) != 1 ||
            sscanf(argv[2], "%u", &N) != 1) {
                printf("usage: %s <num_threads> <array_size>\n",
                       argv[0]);
                return 1;
        }

        if (N < 0)
            DIE("Vector size overflow\n");

        // Inicializa mutex com atributos padrão
        if(pthread_mutex_init(&lock, NULL))
                DIE("Failed to init mutex\n");

        // Alocação de vetores
        if((threads = malloc(num_threads * sizeof(pthread_t))) == NULL)
                DIE("Threads malloc failed\n");
        if((tasks = malloc(num_threads * sizeof(struct task))) == NULL)
                DIE("Tasks malloc failed\n");
        if((V = malloc(N * sizeof(double))) == NULL)
                DIE("V malloc failed\n");

        fill_array(V, N);

        gettimeofday(&start, NULL);

        // Inicializa threads com atributos padrão.
        // O trabalho é distribuído da forma mais uniforme possível entre threads.
        int threads_with_one_more_work = N % num_threads;
        for (int i = 0; i < num_threads; ++i) {
                int work_size = N / num_threads;
                if (i < threads_with_one_more_work)
                        work_size += 1;
                tasks[i].arr = V + i * work_size;
                tasks[i].size = work_size;
                if(pthread_create(&threads[i], NULL, thread_work, (void *)&tasks[i]))
                        DIE("Failed to create thread %d\n", i)
        }

        // Finaliza threads, ignorando o valor de retorno
        for (int i = 0; i < num_threads; ++i) {
                if(pthread_join(threads[i], NULL))
                        DIE("failed to join thread %d\n", i);
        }

        gettimeofday(&end, NULL);
        double elapsed_time = (end.tv_sec - start.tv_sec) +
                              (end.tv_usec - start.tv_usec) / 1000000.0;
        printf("%.4fs\n", elapsed_time);

        // Se quiser conferir o valor final de max, descomente a linha a seguir:
        // printf("max: %lf\n", max);

        // Destruição do mutex e liberação de memória alocada
        if(pthread_mutex_destroy(&lock))
                DIE("Failed to destroy mutex\n");
        free(threads);
        free(tasks);
        return 0;
}
