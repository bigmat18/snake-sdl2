#include <stdbool.h>
#include "Constants.h"
#include <SDL_ttf.h>

#ifndef STRUCT_H
#define STRUCT_H

typedef enum{
    IDLE = 0,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_LEFT,
    MOVING_DOWN,
} State;

typedef struct {
    int x;
    int y;
} Pos, Food;

struct Snake {
    Pos pos;
    State state;
};

typedef struct {
    Food food;
    bool quit;
    struct Snake snake[MAX_SNAKE_LENGTH];
    int snakeLength;
    double gameSpeed;
    int score;
    TTF_Font *font;
} Game;

#endif
