#include <stdbool.h>

#ifndef STRUCT_H
#define STRUCT_H

typedef enum{
    IDLE = 0,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_LEFT,
    MOVING_DOWN,
} State;

typedef struct
{
    int x;
    int y;
} Pos, Food;

struct Snake
{
    Pos pos;
    State state;
    struct Snake *nextBody;
};

typedef struct
{
    Food food;
    bool quit;
    struct Snake snake;
    double gameSpeed;
    int score;
} Game;

#endif