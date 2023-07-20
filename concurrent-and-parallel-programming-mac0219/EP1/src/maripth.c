#include "lga_base.h"
#include "lga_pth.h"
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t lock;
double max = -1;

struct task {
    byte *g_in;
    byte *g_out;
    int g_min;
    int g_max;
    int g_size;
    int n_threads;
};

static byte get_next_cell(int i, int j, byte *grid_in, int grid_size) {
    byte next_cell = EMPTY;

    for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
        int rev_dir = (dir + NUM_DIRECTIONS/2) % NUM_DIRECTIONS;
        byte rev_dir_mask = 0x01 << rev_dir;

        int di = directions[i%2][dir][0];
        int dj = directions[i%2][dir][1];
        int n_i = i + di;
        int n_j = j + dj;

        if (inbounds(n_i, n_j, grid_size)) {
            if (grid_in[ind2d(n_i,n_j)] == WALL) {
                next_cell |= from_wall_collision(i, j, grid_in, grid_size, dir);
            }
            else if (grid_in[ind2d(n_i, n_j)] & rev_dir_mask) {
                next_cell |= rev_dir_mask;
            }
        }
    }

    return check_particles_collision(next_cell);
}

void * teste(void *arg){
    struct task *t = (struct task *)arg;
    int grid_size=t->g_size;
    for (int i = t->g_min; i < t->g_max; i++) {
        for (int j = 0; j < t->g_size; j++) {
                if (t->g_in[ind2d(i,j)] == WALL)
                    t->g_out[ind2d(i,j)] = WALL;
                else
                    t->g_out[ind2d(i,j)] = get_next_cell(i, j, t->g_in, t->g_size);
        }
    }
    return NULL;
}

static void update(byte *grid_in, byte *grid_out, int grid_size, int num_threads,struct task* tasks) {
    pthread_t *threads;
    threads = malloc(num_threads * sizeof(pthread_t));
    for (int i = 0; i < num_threads; i++) {
        tasks[i].g_in = grid_in;
        tasks[i].g_out = grid_out;
        pthread_create(&threads[i], NULL, teste, (void*)&tasks[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
}

void simulate_pth(byte *grid_1, byte *grid_2, int grid_size, int num_threads) {
    struct task *tasks;
    tasks = malloc(num_threads * sizeof(struct task));
    int param=grid_size/num_threads;
    for (int i = 0; i < num_threads; i++) {
        tasks[i].g_min = i*param;
        tasks[i].g_max = (i+1)*param;
        tasks[i].g_size = grid_size;
        tasks[i].n_threads = num_threads;
    }
    for (int i = 0; i < ITERATIONS/2; i++) {
        update(grid_1, grid_2, grid_size,num_threads,tasks);
        update(grid_2, grid_1, grid_size,num_threads,tasks);
    }
}
