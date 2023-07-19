#include "lga_base.h"
#include "lga_seq.h"

// Encontra o proximo estado da celula em (i, j): grid_out[ind2d(i,j)],
// a partir do estado atual (grid_in)
static byte get_next_cell(int i, int j, byte *grid_in, int grid_size) {
    byte next_cell = EMPTY;

    // Etapa de propagacao:
    // Para cada direcao, verifica se ha particula vindo daquela direcao
    for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {

        // rev_dir: direcao oposta a dir
        int rev_dir = (dir + NUM_DIRECTIONS/2) % NUM_DIRECTIONS;
        byte rev_dir_mask = 0x01 << rev_dir;

        // (n_i, n_j): coordenadas do vizinho da celula (i, j) na direcao dir
        int di = directions[i%2][dir][0];
        int dj = directions[i%2][dir][1];
        int n_i = i + di;
        int n_j = j + dj;

        // Verifica se o vizinho esta dentro do grid
        if (inbounds(n_i, n_j, grid_size)) {

            // Se o vizinho for parede, eh possivel que apareca
            // em (i, j) uma particula que colidiu com a parede
            if (grid_in[ind2d(n_i,n_j)] == WALL) {
                next_cell |= from_wall_collision(i, j, grid_in, grid_size, dir);
            }
            // Caso haja uma particula vindo do vizinho para a celula,
            // atualiza a celula colocando nela essa particula
            else if (grid_in[ind2d(n_i, n_j)] & rev_dir_mask) {
                next_cell |= rev_dir_mask;
            }
        }
    }

    // Etapa de colisao: verifica se apos a propagacao,
    // houve colisao entre particulas em (i, j)
    return check_particles_collision(next_cell);
}

// Atualiza o LGA a partir do estado em grid_in,
// escrevendo o resultado em grid_out
static void update(byte *grid_in, byte *grid_out, int grid_size) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (grid_in[ind2d(i,j)] == WALL)
                grid_out[ind2d(i,j)] = WALL;
            else
                grid_out[ind2d(i,j)] = get_next_cell(i, j, grid_in, grid_size);
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
