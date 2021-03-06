#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

int **init_board();
int get_cell_num(int **, int, int);
void print_board(int **);
int solve(int, int **);
int *get_allowed_vals(int, int, int **, int *);
bool is_board_solved(int **);
bool is_sub_square_solved(int **, int, int);

#define BOARD_LENGTH 9

int main() {
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    srand(time.tv_nsec);

    int **board = init_board();

    int i;
    for (i = 0; i < BOARD_LENGTH; i++) {
        int j;
        for (j = 0; j < BOARD_LENGTH; j++)
        {
            board[i][j] = get_cell_num(board, j, i);
        }
    }

    print_board(board);
    printf("\n");

    solve(0, board);

    print_board(board);

    for (i = 0; i < BOARD_LENGTH; i++) {
        free(board[i]);
    }
    free(board);
    
    return 0;
}

int **init_board() {
    int **board = (int **)(malloc(BOARD_LENGTH * sizeof(int *)));

    int i;
    for (i = 0; i < BOARD_LENGTH; i++)
    {
        board[i] = (int *)(malloc(BOARD_LENGTH * sizeof(int)));
        int j;
        for (j = 0; j < BOARD_LENGTH; j++)
        {
            board[i][j] = 0;
        }
    }
    
    return board;
}

int get_cell_num(int **board, int x, int y) {
    int cell_num = 0;
    int non_zero_num_chance = rand() % 4;
    if (non_zero_num_chance == 0) {
        int num_allowed_vals;
        int *allowed_vals = get_allowed_vals(x, y, board, &num_allowed_vals);
        if (num_allowed_vals > 0) {
            cell_num = allowed_vals[rand() % num_allowed_vals];
        }
        free(allowed_vals);
    }
    return cell_num;
}

void print_board(int **board)
{
    int i;
    for (i = 0; i < BOARD_LENGTH; i++)
    {
        int j;
        for (j = 0; j < BOARD_LENGTH; j++)
        {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

int solve(int pos, int **board) {
    int x = pos % BOARD_LENGTH;
    int y = pos / BOARD_LENGTH;
    if (pos >= (BOARD_LENGTH * BOARD_LENGTH)) {
        if (is_board_solved(board))
        {
            return 0;
        }
        
        return 1;
    }
    else if (board[y][x] == 0)
    {
        int num_allowed_vals;
        int *allowed_vals = get_allowed_vals(x, y, board, &num_allowed_vals);

        if (num_allowed_vals == 0) {
            free(allowed_vals);
            return 1;
        }
        else
        {
            bool solved = false;
            int i = 0;
            while (!solved && i < num_allowed_vals)
            {
                board[y][x] = allowed_vals[i];
                int r = solve(pos + 1, board);
                if (r == 0) {
                    solved = true;
                }
                i += 1;
            }

            free(allowed_vals);

            if (solved) {
                return 0;
            }
            else
            {
                board[y][x] = 0;
                return 1;
            }
        }
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

bool is_board_solved(int **board) {
    int i;
    for (i = 0; i < BOARD_LENGTH; i++)
    {
        int j;
        for (j = 0; j < BOARD_LENGTH; j++)
        {
            if (board[i][j] == 0) {
                return false;
            }

            int k;
            for (k = 0; k < BOARD_LENGTH; k++)
            {
                if (j != k && board[i][j] == board[i][k])
                {
                    return false;
                }
                if (j != k && board[j][i] == board[k][i]) {
                    return false;
                }
            }
        }
    }

    int sub_square_length = (int) sqrt(BOARD_LENGTH);
    for (i = 0; i < sub_square_length; i++)
    {
        int j;
        for (j = 0; j < sub_square_length; j++)
        {
            int sub_square_x = j * sub_square_length;
            int sub_square_y = i * sub_square_length;
            if (!is_sub_square_solved(board, sub_square_x, sub_square_y)) {
                return false;
            }
        }
    }
    
    return true;
}

bool is_sub_square_solved(int **board, int x_start, int y_start) {
    int sub_square_length = (int) sqrt(BOARD_LENGTH);
    int row;
    for (row = y_start; row < (y_start + sub_square_length); row++)
    {
        int col;
        for (col = x_start; col < (x_start + sub_square_length); col++)
        {
            int i;
            for (i = y_start; i < (y_start + sub_square_length); i++) {
                int j;
                for (j = x_start; j < (x_start + sub_square_length); j++)
                {
                    if ((i != row || j != col) && board[i][j] == board[row][col]) {
                        return false;
                    }
                    if (board[i][j] == 0) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}