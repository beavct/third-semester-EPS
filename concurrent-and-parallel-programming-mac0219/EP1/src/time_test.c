#include "lga_base.h"
#include "lga_seq.h"
#include "lga_omp.h"
#include "lga_pth.h"
#include "time_extra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOT_READ -1
#define SEQ 0
#define OMP 1
#define PTH 2

void print_usage_message() {
    printf("Uso: ./time_test --grid_size <grid_size> "
        " --impl <impl> --num_threads <num_threads>\n");
    printf("<impl> = seq, omp, pth\n");
    printf("Se impl=seq, num_threads eh ignorado\n");
}

void parse_arguments(int argc, char *argv[], int *grid_size_ptr, int *impl_ptr, int *num_threads_ptr) {
    int ret;

    if (argc != 5 && argc != 7){
        print_usage_message();
        exit(EXIT_FAILURE);
    }

    *grid_size_ptr = NOT_READ;
    *impl_ptr = NOT_READ;
    *num_threads_ptr = NOT_READ;

    for (int i = 0; i < argc-1; i++) {
        if (strcmp(argv[i], "--grid_size") == 0) {
            ret = sscanf(argv[i+1], "%d", grid_size_ptr);
            if (ret == 0 || ret == EOF) {
                fprintf(stderr, "Error reading grid_size\n");
                exit(EXIT_FAILURE);
            }
        }

        if (strcmp(argv[i], "--impl") == 0) {
            if (strcmp(argv[i+1], "seq") == 0) {
                *impl_ptr = SEQ;
            } else if (strcmp(argv[i+1], "omp") == 0) {
                *impl_ptr = OMP;
            } else if (strcmp(argv[i+1], "pth") == 0) {
                *impl_ptr = PTH;
            } else {
                fprintf(stderr, "Error reading impl\n");
                exit(EXIT_FAILURE);
            }
        }

        if (strcmp(argv[i], "--num_threads") == 0) {
            ret = sscanf(argv[i+1], "%d", num_threads_ptr);
            if (ret == 0 || ret == EOF) {
                fprintf(stderr, "Error reading num_threads\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (*grid_size_ptr == NOT_READ || *impl_ptr == NOT_READ) {
        print_usage_message();
        exit(EXIT_FAILURE);
    }


    if (*grid_size_ptr < MIN_GRID_SIZE || *grid_size_ptr > MAX_GRID_SIZE) {
        printf("Invalid grid_size %d (min=%d, max=%d)\n",
            *grid_size_ptr, MIN_GRID_SIZE, MAX_GRID_SIZE);
        exit(EXIT_FAILURE);
    }

    if (*impl_ptr != SEQ) {
        if (*num_threads_ptr == NOT_READ) {
            print_usage_message();
            exit(EXIT_FAILURE);
        }
        if (*num_threads_ptr < MIN_NUM_THREADS || *num_threads_ptr > MAX_NUM_THREADS) {
            printf("Invalid num_threads %d (min=%d, max=%d)\n",
                *num_threads_ptr, MIN_NUM_THREADS, MAX_NUM_THREADS);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[]) {
    byte *grid_1;
    byte *grid_2;
    int grid_size, impl, num_threads;
    struct timeval t1, t2, t3;

    parse_arguments(argc, argv, &grid_size, &impl, &num_threads);

    grid_1 = allocate_grid(grid_size);
    grid_2 = allocate_grid(grid_size);

    initialize_grids(grid_1, grid_2, grid_size);

    gettimeofday(&t1, NULL);
    switch (impl) {
        case SEQ:
            simulate_seq(grid_1, grid_2, grid_size);
            break;
        case OMP:
            simulate_omp(grid_1, grid_2, grid_size, num_threads);
            break;
        case PTH:
            simulate_pth(grid_1, grid_2, grid_size, num_threads);
            break;
    }
    gettimeofday(&t2, NULL);

    timeval_subtract(&t3, &t2, &t1);

    printf("%lu.%06lu\n", t3.tv_sec, t3.tv_usec);

    free(grid_1);
    free(grid_2);

    return 0;
}
