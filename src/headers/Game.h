#include "Struct.h"
#include <SDL2/SDL.h>

#ifndef GAME_H
#define GAME_H

void initGame(Game *game);
void initSnake(Game *game);
void initFood(Game *game);

void setSnakeState(Game *game, State newState);
void updateSnakePosition(Game *game);
bool isSnakeMovementAllowed(Game *game);

bool hasSnakeCollidedFood(Game *game);
void updateGameAfterCollision(Game *game);

#endif

