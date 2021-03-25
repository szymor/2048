#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern int score;
extern int best_score;
extern int board[4][4];
extern int board_size;

// get_best_score_from_file loads the best saved score from best_score.txt and puts it to best_score
void get_best_score_from_file(void) {

    if(access("./best_score.txt", F_OK) != 0) {
        return;
    }

    FILE *fp;
    char buff[10];
    fp = fopen("./best_score.txt", "r");
    fscanf(fp, "%s", buff);
    int bs;
    sscanf(buff, "%d", &bs);
    best_score = bs;

}

// save_best_score_to_file puts the best score (from global var best_score) to best_score.txt
void save_best_score_to_file(void) {

    best_score = score;
    FILE *fp = fopen("./best_score.txt", "w");
    char snum[5];
    sprintf(snum, "%d", best_score);
    fputs(snum, fp);
    fclose(fp);

}

void debug_print_board(char prefix[]) {

    printf("\n%s\n", prefix);
    int a;
    for(a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size; b++) {
            printf("%d ", board[a][b]);
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);

}

// reset_board makes the board empty and spawns two 2s at a random position
void reset_board(void) {

    int a;
    for(a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size; b++) {
            board[a][b] = 0;
        }
    }

    int r1 = rand() % board_size;
    int r2 = rand() % board_size;
    board[0][r1] = 1;
    board[1][r2] = 1;

    //debug_print_board("On reset board");

}

// overwrite_global_board overwrites local_board to the global board
void overwrite_global_board(int local_board[board_size][board_size]) {

    int a;
    for(a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size; b++) {
            board[a][b] = local_board[a][b];
        }
    }

}

// 0 = lost, 1 = not over, 2 = win
int determine_game_state(void) {

    int a;

    // if it finds a 2048 tile, return status 2
    for(a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size; b++) {
            if(board[a][b] == 11) {
                return 2;
            }
        }
    }

    // if zero tile is found, return status 1
    for(a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size; b++) {
            if(board[a][b] == 0) {
                return 1;
            }
        }
    }

    // check for same cells touching horizontally
    for(a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size-1; b++) {
            if(board[a][b] == board[a][b+1]) {
                return 1;
            }
        }
    }

    // check for same cells touching vertically
    for (a = 0; a < board_size; a++) {
        int b;
        for(b = 0; b < board_size-1; b++) {
            if(board[b][a] == board[b+1][a]) {
                return 1;
            }
        }
    }

    return 0;

}

// spawn_2_on_random creates a 2 on a random position and adds it to the board. Note: it doesn't animate it!
void spawn_2_on_random(int* posx, int* posy) {

    int i, zeros;
    for(i = 0; i < board_size; i++) {
        int j;
        for(j = 0; j < board_size; j++) {
            if(board[i][j] == 0) {
                zeros++;
            }
        }
    }

    if(zeros == 0) {
        *posx = -1;
        *posy = -1;
        return;
    }

    int r = rand() % board_size;
    int c = rand() % board_size;

    while(board[r][c] != 0) {
        r = rand() % board_size;
        c = rand() % board_size;
    }

    board[r][c] = 1;
    *posx = c;
    *posy = r;

}

// compress compresses the board
int compress(void) {

    int changed = 0;
    int new_board[board_size][board_size];
    memset(new_board, 0, board_size*board_size*sizeof(int));

    int i;
    for(i = 0; i < board_size; i++) {
        int pos = 0;
        int j;
        for(j = 0; j < board_size; j++) {

            if(board[i][j] != 0) {

                new_board[i][pos] = board[i][j];
                if(j != pos) {
                    changed = 1;
                }
                pos++;

            }

        }
    }

    overwrite_global_board(new_board);
    return changed;

}

// merge merges the horizontally touching cells with the same value. example:
int merge(void) {

    int changed = 0;

    int i;
    for(i = 0; i < board_size; i++) {
        int j;
        for(j = 0; j < board_size-1; j++) {
            if(board[i][j] == board[i][j+1] && board[i][j] != 0) {
                int toadd = (int) pow(2, board[i][j]) * 2;
                score += toadd;
                board[i][j]++;
                board[i][j+1] = 0;
                changed = 1;
            }
        }
    }

    return changed;

}

// reverse reverses the board horizontally. example:
// 0 1 2    2 1 0
// 3 4 5 -> 5 4 3
// 6 7 8    8 7 6
void reverse(void) {

    int new_board[board_size][board_size];
    memset(new_board, 0, board_size*board_size*sizeof(int));

    int i;
    for(i = 0; i < board_size; i++) {
        int j;
        for(j = 0; j < board_size; j++) {
            new_board[i][j] = board[i][board_size-1-j];
        }
    }

    overwrite_global_board(new_board);

}

// transpose reverses the X and Y of all the tiles. example:
// 0 1 2    0 3 6
// 3 4 5 -> 1 4 7
// 6 7 8    2 5 8
void transpose(void) {

    int new_board[board_size][board_size];
    memset(new_board, 0, board_size*board_size*sizeof(int));

    int i;
    for(i = 0; i < board_size; i++) {
        int j;
        for(j = 0; j < board_size; j++) {
            new_board[i][j] = board[j][i];
        }
    }

    overwrite_global_board(new_board);

}

int move_left() {

    int change1 = compress();
    int change2 = merge();

    int changed = change1 || change2;

    compress();

    return changed;

}

int move_right() {

    reverse();
    int changed = move_left();
    reverse();

    return changed;

}

int move_up() {

    transpose();
    int changed = move_left();
    transpose();

    return changed;

}

int move_down() {

    transpose();
    int changed = move_right();
    transpose();

    return changed;

}
