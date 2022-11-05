#include <stdio.h>   
#include <SDL2/SDL.h>

#include "headers/Constants.h"
#include "headers/Struct.h"
#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Game.h"


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