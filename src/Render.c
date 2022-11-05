#include "Render.h"
#include "Utils.h"

#ifndef CELL_WIDTH

#define SCREEN_WIDTH 500
#define BOARD_WIDTH 20
#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))

#endif

#ifndef CELL_HEIGHT

#define SCREEN_HEIGHT 500
#define BOARD_HEIGHT 20
#define CELL_HEIGHT ((SCREEN_HEIGHT / BOARD_HEIGHT))

#endif

void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
    SDL_RenderClear(renderer);

    renderSnake(renderer, game);
    renderFood(renderer, game);

    SDL_RenderPresent(renderer);
}

void renderFood(SDL_Renderer *renderer, Game *game){
    renderSquare(renderer, game->food, 255, 0, 0, 255);
}

void renderSnake(SDL_Renderer *renderer, Game *game){
    struct Snake *currentBody = &(game->snake);
    while(currentBody){
        renderSquare(renderer, currentBody->pos, 0, 255, 0, 255);
        currentBody = currentBody->nextBody;
    }
}

void renderSquare(SDL_Renderer *renderer, Pos position, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    scc(SDL_SetRenderDrawColor(renderer, r, g, b, a));

    SDL_Rect rect = {
        (int)floorf(position.x * CELL_WIDTH),
        (int)floorf(position.y * CELL_HEIGHT),
        (int)floorf(CELL_WIDTH),
        (int)floorf(CELL_HEIGHT),
    };

    scc(SDL_RenderFillRect(renderer, &rect));
}