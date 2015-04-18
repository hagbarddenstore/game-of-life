#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void show(void *universe, int width, int height);
void evolve(void *universe, int weight, int height);
void game(int width, int height);

int main(int argc, char **argv) {
    int width = 0;
    int height = 0;

    if (argc > 1) {
        width = atoi(argv[1]);
    }

    if (argc > 2) {
        height = atoi(argv[2]);
    }

    if (width <= 0) {
        width = 30;
    }

    if (height <= 0) {
        height = 30;
    }

    game(width, height);

    return 0;
}

void show(void *universe, int width, int height) {
    int (*univ)[width] = universe;

    printf("\033[H");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf(univ[y][x] ? "\033[07m  \033[m" : "  ");
        }

        printf("\n");
    }

    fflush(stdout);
}

void evolve(void *universe, int width, int height) {
    unsigned (*univ)[width] = universe;
    unsigned newUniverse[height][width];

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int n = 0;

            for (int y1 = y - 1; y1 <= y + 1; y1++) {
                for (int x1 = x - 1; x1 <= x + 1; x1++) {
                    if (univ[(y1 + height) % height][(x1 + width) % width]) {
                        n++;
                    }
                }
            }

            if (univ[y][x]) {
                n--;
            }

            newUniverse[y][x] = (n == 3 || (n == 2 && univ[y][x]));
        }
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            univ[y][x] = newUniverse[y][x];
        }
    }
}

void game(int width, int height) {
    unsigned universe[height][width];

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            universe[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
        }
    }

    while (1) {
        show(universe, width, height);

        evolve(universe, width, height);

        usleep(20000);
    }
}
