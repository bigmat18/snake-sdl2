#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Game.h"
#include "headers/Constants.h"

#include <time.h>
#include <sys/time.h>
#include <stdbool.h>


void initGame(Game *game) {
    game->quit = false;
    game->gameSpeed = MAX_SNAKE_MOVEMENT;
    game->score = 0;

    initSnake(game);
    initFood(game);
}

void initSnake(Game *game) {
    game->snake[0].pos = getRandomBoardPosition(game);
    game->snake[0].state = IDLE;
    game->snakeLength = 1;
}

void initFood(Game *game) { game->food = getRandomBoardPosition(game); }

void setSnakeState(Game *game, State newState) {
    State oldState;

    for(int i=0; i<game->snakeLength; i++){
        oldState = game->snake[i].state;
        game->snake[i].state = newState;
        newState = oldState;
    }
}

void updateSnakePosition(Game *game, bool manual) {
    if(!isSnakeMovementAllowed(game, manual))
        return;

    if(!manual) setSnakeState(game, game->snake[0].state);    

    for(int i=0; i<game->snakeLength; i++){
        switch(game->snake[i].state){
            case MOVING_RIGHT:{
                if(game->snake[i].pos.x + 1 < BOARD_WIDTH)
                    game->snake[i].pos.x++;
                else game->snake[i].pos.x = 0;
                break;
            }
            case MOVING_LEFT: {
                if (game->snake[i].pos.x - 1 >= 0)
                    game->snake[i].pos.x--;
                else game->snake[i].pos.x = BOARD_WIDTH;
                break;
            }
            case MOVING_DOWN: {
                if (game->snake[i].pos.y + 1 < BOARD_WIDTH)
                    game->snake[i].pos.y++;
                else game->snake[i].pos.y = 0;
                break;
            }
            case MOVING_UP: {
                if (game->snake[i].pos.y - 1 >= 0)
                    game->snake[i].pos.y--;
                else game->snake[i].pos.y = BOARD_HEIGHT;
                break;
            }
            default: {
                break;
            }
        }
    }
    
}

bool isSnakeMovementAllowed(Game *game, bool manual){
    if(manual) return true;

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
    return game->snake[0].pos.x == game->food.x && game->snake[0].pos.y == game->food.y;
}

void updateGameAfterCollision(Game *game){
    game->food = getRandomBoardPosition(game);
    game->score++;

    if (game->gameSpeed -= STEP_SNAKE_MOVEMENT >= MIN_SNAKE_MOVEMENT)
        game->gameSpeed -= STEP_SNAKE_MOVEMENT;

    int newBodyX = game->snake[game->snakeLength-1].pos.x;
    int newBodyY = game->snake[game->snakeLength-1].pos.y;

    switch(game->snake[game->snakeLength-1].state){
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
    struct Snake newBody = {newPos, game->snake[game->snakeLength - 1].state};
    game->snake[game->snakeLength] = newBody;
    game->snakeLength++;
}
