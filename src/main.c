#include <stdio.h>   
#include <SDL2/SDL.h>

#include "Struct.h"
#include "Render.h"
#include "Utils.h"
#include "Game.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))
#define CELL_HEIGHT ((SCREEN_HEIGHT / BOARD_HEIGHT))

#define MAX_SNAKE_MOVEMENT 0.18
#define MIN_SNAKE_MOVEMENT 0.06
#define STEP_SNAKE_MOVEMENT 0.02


Game GAME = {false};

// ------------------------
int main(void){
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *const window = scp(SDL_CreateWindow("Snake Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *const renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    initGame(&GAME);

    while (!GAME.quit){

        // Event handling
        SDL_Event event;

        if(SDL_PollEvent(&event)){
            
            if(event.type == SDL_QUIT)
                GAME.quit = true;

            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.scancode){
                    case SDL_SCANCODE_UP: {
                        setSnakeState(&GAME, MOVING_UP);
                        break;
                    }
                    case SDL_SCANCODE_DOWN: {
                        setSnakeState(&GAME, MOVING_DOWN);
                        break;
                    }
                    case SDL_SCANCODE_LEFT: {
                        setSnakeState(&GAME, MOVING_LEFT);
                        break;
                    }
                    case SDL_SCANCODE_RIGHT: {
                        setSnakeState(&GAME, MOVING_RIGHT);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }
        if(isSnakeMovementAllowed(&GAME))
            updateSnakePosition(&GAME);

        if(hasSnakeCollidedFood(&GAME))
            updateGameAfterCollision(&GAME);

        renderGame(renderer, &GAME);
    }

    return 0;
}