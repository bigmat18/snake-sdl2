#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Game.h"

#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

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

#ifndef MAX_SNAKE_MOVEMENT
#define MAX_SNAKE_MOVEMENT 0.18
#endif

#ifndef MIN_SNAKE_MOVEMENT
#define MIN_SNAKE_MOVEMENT 0.06
#endif

#ifndef STEP_SNAKE_MOVEMENT
#define STEP_SNAKE_MOVEMENT 0.02
#endif



void initGame(Game *game) {
    game->quit = false;
    game->gameSpeed = MAX_SNAKE_MOVEMENT;
    game->score = 0;

    initSnake(game);
    initFood(game);
}

void initSnake(Game *game) {
    game->snake.pos = getRandomBoardPosition(game);
    game->snake.nextBody = NULL;
    game->snake.state = IDLE;
}

void initFood(Game *game) { game->food = getRandomBoardPosition(game); }

void setSnakeState(Game *game, State newState) {
    State oldState;
    struct Snake *currentBody = &(game->snake);

    while(currentBody){
        oldState = currentBody->state;
        currentBody->state = newState;
        newState = oldState;
        currentBody = currentBody->nextBody;
    }
}

void updateSnakePosition(Game *game) {
    struct Snake *currentBody = &(game->snake);

    while (currentBody){
        switch(currentBody->state){
            case MOVING_RIGHT:{
                if(currentBody->pos.x + 1 < 20)
                    currentBody->pos.x++;
                break;
            }
            case MOVING_LEFT: {
                if (currentBody->pos.x - 1 >= 0)
                    currentBody->pos.x--;
                break;
            }
            case MOVING_DOWN: {
                if (currentBody->pos.y + 1 < 20)
                    currentBody->pos.y++;
                break;
            }
            case MOVING_UP: {
                if (currentBody->pos.y - 1 >= 0)
                    currentBody->pos.y--;
                break;
            }
            default: {
                break;
            }
        }
        currentBody = currentBody->nextBody;
    }
    
}

bool isSnakeMovementAllowed(Game *game){
    static struct timeval oldTime = {0};
    static struct timeval newTime = {0};
    static bool init = false;
    double elapsed = -1;

    if(!init){
        init = true;
        gettimeofday(&oldTime, NULL);
        return true;
    }

    gettimeofday(&newTime, NULL);
    elapsed = (double)(newTime.tv_usec - oldTime.tv_usec) / 1000000 +
              (double)(newTime.tv_sec - oldTime.tv_sec);

    if(elapsed < game->gameSpeed){
        return false;
    }else{
        oldTime = newTime;
        return true;
    }

}

bool hasSnakeCollidedFood(Game *game){
    return game->snake.pos.x == game->food.x && game->snake.pos.y == game->food.y;
}

void updateGameAfterCollision(Game *game){
    game->food = getRandomBoardPosition(game);
    game->score++;

    if (game->gameSpeed -= STEP_SNAKE_MOVEMENT >= MIN_SNAKE_MOVEMENT)
        game->gameSpeed -= STEP_SNAKE_MOVEMENT;

    struct Snake *currentBody = &(game->snake);
    while (currentBody->nextBody){
        currentBody = currentBody->nextBody;
    }

    int newBodyX = currentBody->pos.x;
    int newBodyY = currentBody->pos.y;

    switch(currentBody->state){
        case MOVING_RIGHT:{
            newBodyX --;
            break;
        }
        case MOVING_LEFT: {
            newBodyX ++;
            break;
        }
        case MOVING_DOWN: {
            newBodyY--;
            break;
        }
        case MOVING_UP: {
            newBodyY++;
            break;
        }
        default: {
            break;
        }
    }
    Pos newPos = {newBodyX, newBodyY};
    struct Snake newBody = {newPos, currentBody->state, NULL};
    currentBody->nextBody = &newBody;
}
