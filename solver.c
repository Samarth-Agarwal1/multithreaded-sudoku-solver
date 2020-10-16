#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_cell_num();
int solve(int, int **);

#define BOARD_LENGTH 9

int main() {
    int **board = (int **)(malloc(BOARD_LENGTH * sizeof(int *)));
    int i;
    int j;
    for (i = 0; i < BOARD_LENGTH; i++) {
        board[i] = (int *)(malloc(BOARD_LENGTH * sizeof(int)));
        for (j = 0; j < BOARD_LENGTH; j++)
        {
            board[i][j] = get_cell_num();
        }
    }

    for (i = 0; i < BOARD_LENGTH; i++)
    {
        for (j = 0; j < BOARD_LENGTH; j++)
        {
            printf("%2d ", board[i][j]);
        }
        printf("\n");     
    }

    solve(0, board);
    
    return 0;
}

int get_cell_num() {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    srand(time.tv_nsec);
    int non_zero_num_chance = rand() % 11;
    if (non_zero_num_chance == 0) {
        return rand() % BOARD_LENGTH;
    }
    return 0;
}

int solve(int pos, int **board) {
    int x = pos % BOARD_LENGTH;
    int y = pos / BOARD_LENGTH;
    if (pos >= (BOARD_LENGTH * BOARD_LENGTH)) {
        return 0;
    }
    else if (board[y][x] == 0)
    {
        return 0;
    }

    return 0;
}