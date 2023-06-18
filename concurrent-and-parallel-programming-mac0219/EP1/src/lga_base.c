#include "lga_base.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    Vetor que indica as coordenadas do vizinho de cada posicao i,j no grid hexagonal
    Vizinho de i,j == i + directions[i%2][dir][0], j + directions[i%2][dir][1]
    dir = 0, 1, 2, 3, 4 ou 5 de acordo com o esquema:

     2   1
      \ /
    3 - - 0
      / \
     4   5
*/
int directions[2][6][2] = {
    {{0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, 0}, {1, 1}},
    {{0, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}}
};

// Aloca grid na memoria
byte *allocate_grid(int grid_size) {
    byte *grid = (byte*) calloc(grid_size*grid_size, sizeof(byte));

    if (!grid) {
        fprintf(stderr, "Error allocating grid\n");
        exit(EXIT_FAILURE);
    }

    return grid;
}

// Le o estado inicial do grid de um arquivo x.in, onde x == grid_size
void read_grid_from_file(byte *grid, int grid_size) {
    FILE *file_ptr;
    char filename[8];

    snprintf(filename, sizeof(filename), "%d.in", grid_size);

    file_ptr = fopen(filename, "rb");
    if (!file_ptr) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int total_bytes = grid_size * grid_size;
    size_t total_read = fread(grid, sizeof(byte), total_bytes, file_ptr);
    if (total_read != (size_t) total_bytes) {
        fprintf(stderr, "Error reading file, read %lu bytes out of %d\n", total_read, total_bytes);
        exit(EXIT_FAILURE);
    }

    fclose(file_ptr);
}

// Determina o valor inicial dos grids, lendo o grid_1 do arquivo
// e copiando inicialmente apenas as paredes pra o grid_2
void initialize_grids(byte *grid_1, byte *grid_2, int grid_size) {
    read_grid_from_file(grid_1, grid_size);

    // Como as paredes sao fixas durante a simulacao,
    // basta inseri-las no grid auxiliar
    // uma vez durante a inicializacao
    for (int idx = 0; idx < grid_size*grid_size; idx++) {
        if (grid_1[idx] == WALL)
            grid_2[idx] = WALL;
        else
            grid_2[idx] = EMPTY;
    }
}

// Tentativa de implementar uma colisao um pouco mais realista com
// as paredes, que nao seja apenas uma reflexao simples
void wall_collision(int i, int j, byte *grid_out, int grid_size, int dir) {
    // Reflexao simples:
    // byte dir_mask = 0x01 << dir;
    // grid_out[ind2d(i,j)] |= ((dir_mask << 3) | (dir_mask >> 3)) % WALL;

    if (dir == 0) {
        grid_out[ind2d(i,j)] |= 0x08;
    }
    else if (dir == 1) {
        if (inbounds(i-2, j, grid_size) && grid_out[ind2d(i-2,j)] != WALL)
            grid_out[ind2d(i-2,j)] |= 0x04;
        else if (inbounds(i, j+1, grid_size) && grid_out[ind2d(i,j+1)] != WALL)
            grid_out[ind2d(i,j+1)] |= 0x20;
        else
            grid_out[ind2d(i,j)] |= 0x10;

    } else if (dir == 2) {
        if (inbounds(i-2, j, grid_size) && grid_out[ind2d(i-2,j)] != WALL)
            grid_out[ind2d(i-2,j)] |= 0x02;
        else if (inbounds(i, j-1, grid_size) && grid_out[ind2d(i,j-1)] != WALL)
            grid_out[ind2d(i,j-1)] |= 0x10;
        else
            grid_out[ind2d(i,j)] |= 0x20;

    } else if (dir == 3) {
        grid_out[ind2d(i,j)] |= 0x01;

    } else if (dir == 4) {
        if (inbounds(i+2, j, grid_size) && grid_out[ind2d(i+2,j)] != WALL)
            grid_out[ind2d(i+2,j)] |= 0x20;
        else if (inbounds(i, j-1, grid_size) && grid_out[ind2d(i,j-1)] != WALL)
            grid_out[ind2d(i,j-1)] |= 0x04;
        else
            grid_out[ind2d(i,j)] |= 0x02;

    } else if (dir == 5) {
        if (inbounds(i+2, j, grid_size) && grid_out[ind2d(i+2,j)] != WALL)
            grid_out[ind2d(i+2,j)] |= 0x10;
        else if (inbounds(i, j+1, grid_size) && grid_out[ind2d(i,j+1)] != WALL)
            grid_out[ind2d(i,j+1)] |= 0x02;
        else
            grid_out[ind2d(i,j)] |= 0x04;
    }
}

// Logica de colisao entre particulas de acordo com o modelo
byte particles_collision(byte cell) {
    switch (cell) {
        // Colisao entre duas particulas
        case 0x09:
            return 0x12;
        case 0x12:
            return 0x28;
        case 0x28:
            return 0x09;

        // Colisao entre tres particulas
        case 0x15:
            return 0x2A;
        case 0x2A:
            return 0x15;

        // Colisao entre quatro particulas
        case 0x36:
            return 0x2D;
        case 0x2D:
            return 0x1B;
        case 0x1B:
            return 0x36;

        default:
            return cell;
    }
}

// Imprime o estado atual da simulacao para debug,
// mostrando particulas (*) e paredes (#)
void print_grid(byte *grid, int grid_size) {
    for (int i = 0; i < grid_size; i++) {

        // Para ter aparencia hexagonal
        if (i % 2 == 0)
            printf(" ");

        for (int j = 0; j < grid_size; j++) {
            byte c = grid[ind2d(i,j)];

            if (c == EMPTY)
                printf("  ");
            else if (c == WALL)
                printf("# ");
            else
                printf("* ");
        }
        printf("\n");
    }
}

// Imprime o estado atual da simulacao para gerar uma 
// animacao ASCII da simulacao
void print_grid_animation(byte *grid, int grid_size) {
    for (int i = 0; i < grid_size; i++) {
        printf("\"");
        if (i % 2 == 0)
            printf(" ");
        for (int j = 0; j < grid_size; j++) {
            byte c = grid[ind2d(i,j)];

            if (c == EMPTY)
                printf("  ");
            else if (c == WALL)
                printf("# ");
            else
                printf("* ");
        }
        // TODO: remover ultima virgula no arquivo
        // Do jeito que esta, isso deve ser feito manualmente
        if (i == grid_size - 1)
            printf("\"+a,\n");
        else
            printf("\"+a+\n");
    }
}

// Imprime o estado atual da simulacao para debug,
// mostrando o valor numerico de cada celula
void print_grid_numbers(byte *grid, int grid_size) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            printf("%-3d", grid[ind2d(i,j)]);
        }
        printf("\n");
    }
}
