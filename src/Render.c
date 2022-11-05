#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Constants.h"


void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR)));
    SDL_RenderClear(renderer);

    renderSnake(renderer, game);
    renderFood(renderer, game);

    SDL_RenderPresent(renderer);
}

void renderFood(SDL_Renderer *renderer, Game *game){
    renderSquare(renderer, game->food, HEX_COLOR(FOOD_COLOR));
}

void renderSnake(SDL_Renderer *renderer, Game *game){
    for(int i=0; i<game->snakeLength; i++)
        renderSquare(renderer, game->snake[i].pos, HEX_COLOR(SNAKE_COLOR));
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