#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "main.h"
#include "game.h"
#include "graphics.h"

int main(void) {

    srand(time(NULL));

    // attempt to initialize graphics and timer systema
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);

    SDL_Surface * screen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
    if (!screen)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }
    SDL_ShowCursor(SDL_DISABLE);

    // load background
    backgroundIMG = load_asset("assets/base.png");
    // load board (overwritten when 4x4 board is selected)
    boardIMG = load_asset("assets/3/board.png");
    // load tiles (overwritten when 4x4 board is selected)
    tilesIMG = load_asset("assets/3/tiles.png");
    // load prerendered numbers for the score
    fontIMG = load_asset("assets/numbers.png");

    SDL_Flip(screen);    
    gameLoop(screen);

    SDL_Quit();
    
}
