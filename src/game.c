#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "graphics.h"
#include "logic.h"

int score = 0;
int best_score = 0; // the best score will be loaded at the first call to clear_screen
int board_size = 3; // by default the board is 3x3

int board[4][4]; // we'll make it 4x4 because it's the biggest size possible and downscaling isn't a problem

void gameLoop(SDL_Surface * screen) {

    while (1){ //restarts automatically when game is lost

        reset_board();
        clear_screen(screen);
        SDL_Flip(screen);

        score = 0;

        get_best_score_from_file();
        //get_board_from_file(); not implemented yet

        int game_over = 0;
        while (!game_over) { //handles game over

            SDL_Delay(100);
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    return;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE: //Select
                        return;
                    case SDLK_RETURN:
                        game_over = 1;
                        break;
                    case SDLK_LCTRL: // A button
                    case SDLK_RIGHT: // right
                        move_board(3, screen);
                        break;
                    case SDLK_LSHIFT: // Y button
                    case SDLK_LEFT: // left
                        move_board(2, screen);
                        break;
                    case SDLK_LALT: // B button
                    case SDLK_DOWN: // down
                        move_board(1, screen);
                        break;
                    case SDLK_SPACE: // X button
                    case SDLK_UP: // up
                        move_board(0, screen);
                        break;             
                    default:
                        break;
                    }
                }
            }

            clear_screen(screen);
            SDL_Flip(screen);

            switch(determine_game_state()) {
            case 0: // game is over
                game_over = 1;
                break;
            case 1: // game is still in progress
                break;
            case 2: // game is won
                game_won_animation(screen);
                game_over = 1;
                break;
            }
            
        }

        game_over_animation(screen);

    }

}