#include <stdio.h>   
#include <SDL2/SDL.h>

#include "headers/Constants.h"
#include "headers/Struct.h"
#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Game.h"


Game GAME = {false};


int main(void){
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *const window = scp(SDL_CreateWindow("Snake Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *const renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    initGame(&GAME);

    bool manual = false;

    while (!GAME.quit){

        // Event handling
        SDL_Event event;
        manual = false;

        if(SDL_PollEvent(&event)){
            
            if(event.type == SDL_QUIT)
                GAME.quit = true;

            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.scancode){
                    case SDL_SCANCODE_UP: {
                        if (GAME.snake[0].state != MOVING_DOWN){
                            setSnakeState(&GAME, MOVING_UP);
                            manual = true;
                        }
                        break;
                    }
                    case SDL_SCANCODE_DOWN: {
                        if (GAME.snake[0].state != MOVING_UP){
                            setSnakeState(&GAME, MOVING_DOWN);
                            manual = true;
                        }
                        break;
                    }
                    case SDL_SCANCODE_LEFT: {
                        if (GAME.snake[0].state != MOVING_RIGHT){
                            setSnakeState(&GAME, MOVING_LEFT);
                            manual = true;
                        }
                        break;
                    }
                    case SDL_SCANCODE_RIGHT: {
                        if (GAME.snake[0].state != MOVING_LEFT){
                            setSnakeState(&GAME, MOVING_RIGHT);
                            manual = true;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }

        updateSnakePosition(&GAME, manual);

        if(hasSnakeCollidedFood(&GAME))
            updateGameAfterCollision(&GAME);

        GAME.quit = hasSnakeCollidedHimSelf(&GAME);
            
        renderGame(renderer, &GAME);
    }

    return 0;
}