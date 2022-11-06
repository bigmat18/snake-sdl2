#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Constants.h"
#include <SDL_ttf.h>


void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, HEX_COLOR(BACKGROUND_COLOR)));
    SDL_RenderClear(renderer);

    renderSnake(renderer, game);
    renderFood(renderer, game);
    renderScore(renderer, game);

    SDL_RenderPresent(renderer);
}

void renderFood(SDL_Renderer *renderer, Game *game){
    renderSquare(renderer, game->food, HEX_COLOR(FOOD_COLOR));
}

void renderSnake(SDL_Renderer *renderer, Game *game){
    for(int i=0; i<game->snakeLength; i++)
        renderSquare(renderer, game->snake[i].pos, HEX_COLOR(SNAKE_COLOR));
}

void renderScore(SDL_Renderer *renderer, Game *game){
    static SDL_Surface *surface;
    static SDL_Texture *texture;
    static bool init = false;
    static int previusScore = -1;

    if (previusScore == game->score)
        return;

    if (!init) {
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }

    char str[32];
    sprintf(str, "Score: %d", game->score);

    surface = TTF_RenderText_Solid(game->font, str, (SDL_Color){HEX_COLOR(SCORE_COLOR)});
    
    if(!surface) {
        printf("Error: %s\n", TTF_GetError());
        exit(1);
    }
    
    texture = scp(SDL_CreateTextureFromSurface(renderer, surface));

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = {0, 0, textW, textH};

    SDL_RenderCopy(renderer, texture, NULL, &textRect);
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

