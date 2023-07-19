#include "lga_base.h"
#include "lga_seq.h"
#include "lga_omp.h"
#include "lga_pth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NOT_READ -1

void print_usage_message() {
    printf("Uso: ./check --grid_size <grid_size> --num_threads <num_threads>\n");
}

void parse_arguments(int argc, char *argv[], int *grid_size_ptr, int *num_threads_ptr) {
    int ret;

    if (argc != 5) {
        print_usage_message();
        exit(EXIT_FAILURE);
    }

    *grid_size_ptr = NOT_READ;
    *num_threads_ptr = NOT_READ;

    for (int i = 0; i < argc-1; i++) {
        if (strcmp(argv[i], "--grid_size") == 0) {
            ret = sscanf(argv[i+1], "%d", grid_size_ptr);
            if (ret == 0 || ret == EOF) {
                fprintf(stderr, "Error reading grid_size\n");
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

    if (*grid_size_ptr == NOT_READ || *num_threads_ptr == NOT_READ) {
        print_usage_message();
        exit(EXIT_FAILURE);
    }

    if (*grid_size_ptr < MIN_GRID_SIZE || *grid_size_ptr > MAX_GRID_SIZE) {
        printf("Invalid grid_size %d (min=%d, max=%d)\n",
            *grid_size_ptr, MIN_GRID_SIZE, MAX_GRID_SIZE);
        exit(EXIT_FAILURE);
    }

    if (*num_threads_ptr < MIN_NUM_THREADS || *num_threads_ptr > MAX_NUM_THREADS) {
        printf("Invalid num_threads %d (min=%d, max=%d)\n",
            *num_threads_ptr, MIN_NUM_THREADS, MAX_NUM_THREADS);
        exit(EXIT_FAILURE);
    }
}

bool are_grids_equal(byte* grid_a, byte* grid_b, int grid_size) {
    for (int idx = 0; idx < grid_size*grid_size; idx++)
        if (grid_a[idx] != grid_b[idx])
            return false;

    return true;
}

int main(int argc, char *argv[]) {
    byte *grid_ref;
    byte *grid_1;
    byte *grid_2;
    int grid_size, num_threads;

    parse_arguments(argc, argv, &grid_size, &num_threads);

    grid_ref = allocate_grid(grid_size);
    grid_1 = allocate_grid(grid_size);
    grid_2 = allocate_grid(grid_size);

    printf("Check grid_size=%d, num_threads=%d\n", grid_size, num_threads);
    printf("Executando versao sequencial...\n");
    initialize_grids(grid_ref, grid_2, grid_size);
    simulate_seq(grid_ref, grid_2, grid_size);

    printf("Executando versao OpenMP...\n");
    initialize_grids(grid_1, grid_2, grid_size);
    simulate_omp(grid_1, grid_2, grid_size, num_threads);

    if (are_grids_equal(grid_ref, grid_1, grid_size))
        printf("Resultado OpenMP igual ao sequencial\n");
    else
        printf("Resultado OpenMP DIFERENTE do sequencial\n");

    printf("Executando versao Pthreads...\n");
    initialize_grids(grid_1, grid_2, grid_size);
    simulate_pth(grid_1, grid_2, grid_size, num_threads);

    if (are_grids_equal(grid_ref, grid_1, grid_size))
        printf("Resultado Pthreads igual ao sequencial\n");
    else
        printf("Resultado Pthreads DIFERENTE do sequencial\n");

    free(grid_ref);
    free(grid_1);
    free(grid_2);

    return 0;
}
