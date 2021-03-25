#ifndef GRAPHICS_DOT_H
#define GRAPHICS_DOT_H

void clear_screen(SDL_Surface*);
void game_over_animation(SDL_Surface*);
void game_won_animation(SDL_Surface*);
void print_board(SDL_Surface*);
void move_board(int, SDL_Surface*);

SDL_Surface* load_asset(char path[]);

#endif 