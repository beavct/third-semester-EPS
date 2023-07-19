#include "lga_base.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DENSITY 0.05

// Procedimento auxiliar para inicializar o gerador de
// numeros pseudo-aleatorios (PRNG).
// Utiliza-se o Unix time em microssegundos (us) como seed.
void initialize_prng(void)
{
    struct timeval tv;
    long total_us;

    gettimeofday(&tv, NULL);
    total_us = tv.tv_sec * 1000000 + tv.tv_usec;

    srand(total_us);
}

void generate_grid(byte *grid, int grid_size) {
    int dir;

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (i == 0 || j == 0 || i == grid_size - 1 || j == grid_size - 1) {
                grid[ind2d(i,j)] = WALL;
            } else {
                // https://c-faq.com/lib/randrange.html
                if (rand() < DENSITY * RAND_MAX) {
                    dir = rand() / (RAND_MAX / NUM_DIRECTIONS + 1);
                    grid[ind2d(i,j)] = 0x01 << dir;
                } else {
                    grid[ind2d(i,j)] = EMPTY;
                }
            }
        }
    }
}

void write_grid_to_file(byte *grid, int grid_size) {
    FILE *file_ptr;
    char filename[8];

    snprintf(filename, sizeof(filename), "%d.in", grid_size);

    file_ptr = fopen(filename, "wb");
    if (!file_ptr) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int total_bytes = grid_size * grid_size;
    size_t total_written = fwrite(grid, sizeof(byte), total_bytes, file_ptr);
    if (total_written != (size_t) total_bytes) {
        fprintf(stderr, "Error writing file, wrote %lu bytes out of %d\n", total_written, total_bytes);
        exit(EXIT_FAILURE);
    }

    fclose(file_ptr);
}

int main(int argc, char *argv[]) {
    byte *grid;
    int grid_size;

    if (argc != 2){
        printf("usage: ./grid_gen <grid_size>\n");
        exit(EXIT_FAILURE);
    }

    int ret = sscanf(argv[1], "%d", &grid_size);
    if (ret == 0 || ret == EOF) {
        fprintf(stderr, "Error reading grid_size\n");
        exit(EXIT_FAILURE);
    }
    if (grid_size < MIN_GRID_SIZE || grid_size > MAX_GRID_SIZE) {
        printf("Invalid grid_size %d\n", grid_size);
        exit(EXIT_FAILURE);
    }

    grid = (byte*) calloc(grid_size*grid_size, sizeof(byte));

    if (!grid) {
        fprintf(stderr, "Error allocating grid\n");
        exit(EXIT_FAILURE);
    }

    initialize_prng();

    generate_grid(grid, grid_size);

    write_grid_to_file(grid, grid_size);

    free(grid);

    return 0;
}
