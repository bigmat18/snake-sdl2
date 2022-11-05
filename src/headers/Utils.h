#include "Struct.h"
#include <SDL2/SDL.h>

#ifndef UTILS_H
#define UTILS_H

void scc(int code);
void *scp(void *ptr);

Pos getRandomBoardPosition(Game *game);
Pos getRandomPosition();
int getRandomInt(int max, int min);

#endif