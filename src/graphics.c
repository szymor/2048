#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "logic.h"

extern SDL_Surface* backgroundIMG;
extern SDL_Surface* boardIMG;
extern SDL_Surface* tilesIMG;
extern SDL_Surface* fontIMG;

extern int score;
extern int best_score;
extern int board[4][4];
extern int board_size;

// load_asset is a helper function to reload assets from a file
SDL_Surface* load_asset(char path[]) {

    SDL_Surface* _img = IMG_Load(path);
	SDL_Surface* img = SDL_DisplayFormat(_img);
	SDL_FreeSurface(_img);

    return img;

}

// print_score draws the specified score on the specified screen at the specified coordinates
void print_score(int score_x, int score_y, int number, SDL_Surface * screen) {

    if(number == 0) {

        SDL_Rect SrcR = {x: 0, y: 0, w: 7, h: 9};
        SDL_Rect DestR = {x: score_x, y: score_y};
        SDL_BlitSurface(fontIMG, &SrcR, screen, &DestR);

    }else{

        //(floor(log10(abs(number))) + 1) is the lenght of the number. idk how it works, i copied it from stackoverflow.
        score_x += (floor(log10(abs(number))) + 1) * 7 - 7;

        int digit = 0;
        while (number != 0) {

            SDL_Rect SrcR = {x: number % 10 * 7, y: 0, w: 7, h: 9};
            SDL_Rect DestR = {x: score_x + (7 * digit), y: score_y};
            SDL_BlitSurface(fontIMG, &SrcR, screen, &DestR);

            digit -= 1;
            number /= 10;

        }

    }

}

int get_cells_width(void) {

    int cell_width;
    switch(board_size) {
    case 3:
        cell_width = 53;
        break;
    case 4:
        cell_width = 38;
        break;
    default:
        break;
    }
    return cell_width;

}

// print_board draws the current board from the global variable to the screen
void print_board(SDL_Surface* screen) {

    int cell_width = get_cells_width();

    int i;
    for(i = 0; i < board_size; i++) {

        int j;
        for(j = 0; j < board_size; j++) {

            SDL_Rect SrcR = {x: cell_width * board[i][j], y: 0, w: cell_width, h: cell_width};
            SDL_Rect DestR = {x: 29 + (cell_width + 5) * j, y: 34 + (cell_width + 5) * i};
            SDL_BlitSurface(tilesIMG, &SrcR, screen, &DestR);

        }

    }

}

// clear_screen resets the screen
void clear_screen(SDL_Surface* screen) {

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    SDL_BlitSurface(backgroundIMG, NULL, screen, NULL);

    SDL_Rect DestR = {x: 22, y: 29};
    SDL_BlitSurface(boardIMG, NULL, screen, &DestR);

    print_score(267, 95, score, screen);
    print_score(267, 114, best_score, screen);
    print_board(screen);

}

void change_board_size(int new_size) {

    //printf("Change board size: %d, old size is %d", new_size, board_size);

    if(new_size != board_size) {

        board_size = new_size;

        char board_path[30];
        char tiles_path[30];

        sprintf(board_path, "assets/%d/board.png", (int)new_size);
        sprintf(tiles_path, "assets/%d/tiles.png", (int)new_size);

        boardIMG = load_asset(board_path); 
        tilesIMG = load_asset(tiles_path);

    }

}

void game_over_animation(SDL_Surface* screen) {

    SDL_Delay(1000);

    if(score > best_score) {
        save_best_score_to_file();
    }

    SDL_Surface* _img = IMG_Load("assets/gameover.png");
	SDL_Surface* gameOver = SDL_DisplayFormat(_img);
	SDL_FreeSurface(_img);

    int i;
    for(i=0; i<=20; i++) {

        SDL_SetAlpha(gameOver, SDL_SRCALPHA, i*2.5+5);

        SDL_BlitSurface(gameOver, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(20);

    }

    SDL_SetAlpha(gameOver, 0, 255);
    SDL_BlitSurface(gameOver, NULL, screen, NULL);
    SDL_Flip(screen);

    SDL_FreeSurface(gameOver);

    while(1) {
        SDL_Delay(100);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_LCTRL: // A button
                    change_board_size(4);
                    return;
                case SDLK_LALT: // B button
                    change_board_size(3);
                    return;
                default:
                    return;
                }
            }
        }
    }

}

void game_won_animation(SDL_Surface* screen) {

    if(score > best_score) { //save best score to file
        save_best_score_to_file();
    }

    SDL_Surface* _img = IMG_Load("assets/youwin.png");
	SDL_Surface* youWin = SDL_DisplayFormat(_img);
	SDL_FreeSurface(_img);

    int i;
    for(i=0; i<=20; i++) {

        SDL_SetAlpha(youWin, SDL_SRCALPHA, i*2.5+5);

        SDL_BlitSurface(youWin, NULL, screen, NULL);
        SDL_Flip(screen);
        SDL_Delay(20);

    }

    SDL_SetAlpha(youWin, 0, 255);
    SDL_BlitSurface(youWin, NULL, screen, NULL);
    SDL_Flip(screen);

    SDL_Delay(1000);
    SDL_FreeSurface(youWin);

    while(1) {
        SDL_Delay(100);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                return;
            }
        }
    }

}

void animate_spawning_2(int posx, int posy, SDL_Surface* screen) {

    int cell_width = get_cells_width();

    int a;
    for(a = 0; a < 4; a++) {

        SDL_Rect SrcR = {x: cell_width, y: (3 * cell_width) - a * cell_width, w: cell_width, h: cell_width};
        SDL_Rect DestR = {x: 29 + (cell_width + 5) * posx, y: 34 + (cell_width + 5) * posy};
        SDL_BlitSurface(tilesIMG, &SrcR, screen, &DestR);

        SDL_Flip(screen);
        SDL_Delay(10);

    }

}

void move_board(int direction, SDL_Surface* screen) {

    int changed;

    /*
    0: up
    1: down
    2: left
    3: right
    */
    switch(direction) {
    case 0:
        changed = move_up();
        break;
    case 1:
        changed = move_down();
        break;
    case 2:
        changed = move_left();
        break;
    case 3:
        changed = move_right();
        break;
    }

    SDL_Flip(screen);

    if(changed) {
        int posx, posy;
        spawn_2_on_random(&posx, &posy);
        if(posy != -1 && posx != -1) {
            animate_spawning_2(posx, posy, screen);
        }
    }

    print_board(screen);
    SDL_Flip(screen);

}
