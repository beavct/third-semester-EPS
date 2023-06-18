#include "lga_base.h"
#include "lga_seq.h"

// Atualiza o LGA a partir do estado em grid_in,
// escrevendo o resultado em grid_out
static void update(byte *grid_in, byte *grid_out, int grid_size) {
    // Etapa de propagacao: atualiza posicoes
    // e verifica colisoes com paredes
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            // Para cada celula, para cada direcao, verifica se
            // ha particula indo naquela direcao
            for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
                byte dir_mask = 0x01 << dir;

                // Caso haja uma particula indo na direcao dir,
                // atualiza o vizinho colocando nele uma particula
                // na mesma direcao
                if (grid_in[ind2d(i,j)] & dir_mask) {
                    int di = directions[i%2][dir][0];
                    int dj = directions[i%2][dir][1];
                    int n_i = i + di;
                    int n_j = j + dj;

                    if (inbounds(n_i, n_j, grid_size)) {
                        if (grid_in[ind2d(n_i,n_j)] == WALL)
                            wall_collision(i, j, grid_out, grid_size, dir);
                        
                        // Se estiver dentro dos limites e nao colidir com parede, propaga
                        else
                            grid_out[ind2d(n_i,n_j)] |= dir_mask;

                        // Remove a particula da celula anterior
                        grid_in[ind2d(i,j)] &= ~dir_mask;
                    }
                }
            }
        }
    }

    // Etapa de colisao: verifica colisoes entre particulas
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            grid_out[ind2d(i,j)] = particles_collision(grid_out[ind2d(i,j)]);
        }
    }
}

// Simula ITERATIONS iteracoes do LGA de forma sequencial,
// a partir do estado inicial lido em initialize_grids
void simulate_seq(byte *grid_1, byte *grid_2, int grid_size) {
    // Alterna entre grid_1 e grid_2 como grid "prinicipal"
    // para evitar copias desnecessarias de um para o outro
    for (int i = 0; i < ITERATIONS/2; i++) {
        update(grid_1, grid_2, grid_size);
        update(grid_2, grid_1, grid_size);
    }
}
