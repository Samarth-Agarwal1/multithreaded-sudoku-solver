#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

int get_cell_num();
int solve(int, int **);
int *get_allowed_vals(int, int, int **, int *);

#define BOARD_LENGTH 4

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
        int num_allowed_vals;
        int *allowed_vals = get_allowed_vals(x, y, board, &num_allowed_vals);

        if (num_allowed_vals == 0) {
            return -1;
        }
        return 0;
    }
    else
    {
        return solve(pos + 1, board);
    }
}

int *get_allowed_vals(int x, int y, int **board, int *num_allowed_vals) {
    int *allowed_vals = malloc(sizeof(int) * BOARD_LENGTH);
    *num_allowed_vals = 0;
    int val;
    for (val = 1; val <= BOARD_LENGTH; val++) {
        bool allowed_val = true;
        int i;
        for (i = 0; i < BOARD_LENGTH; i++) {
            if (board[y][i] == val) {
                allowed_val = false;
            }
            else if (board[i][x] == val)
            {
                allowed_val = false;
            }
        }

        int sub_square_length = (int) sqrt(BOARD_LENGTH);
        int sub_square_x = (x / sub_square_length) * sub_square_length;
        int sub_square_y = (y / sub_square_length) * sub_square_length;
        for (i = sub_square_y; i < (sub_square_y + sub_square_length); i++)
        {
            int j;
            for (j = sub_square_x; j < (sub_square_x + sub_square_length); j++)
            {
                if (board[i][j] == val) {
                    allowed_val = false;
                }
            }
        }

        if (allowed_val) {
            allowed_vals[*num_allowed_vals] = val;
            *num_allowed_vals += 1;
        }
    }

    return allowed_vals;
}