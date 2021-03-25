#ifndef LOGIC_DOT_H
#define LOGIC_DOT_H

void reset_board(void);
void spawn_2_on_random(int*, int*);

void get_best_score_from_file(void);
void save_best_score_to_file(void);
void debug_print_board(char[]);
int determine_game_state(void);

int move_right(void);
int move_left(void);
int move_up(void);
int move_down(void);


#endif 