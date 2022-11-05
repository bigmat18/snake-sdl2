#include "Struct.h"
#include <SDL2/SDL.h>

#ifndef RENDER_H
#define RENDER_H


void renderGame(SDL_Renderer *renderer, Game *game);
void renderSnake(SDL_Renderer *renderer, Game *game);
void renderFood(SDL_Renderer *renderer, Game *game);
void renderSquare(SDL_Renderer *renderer, Pos position, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif