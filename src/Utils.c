#include "headers/Render.h"
#include "headers/Utils.h"
#include <stdbool.h>

#ifndef BOARD_WIDTH
#define BOARD_WIDTH 20
#endif

#ifndef BOARD_HEIGHT
#define BOARD_HEIGHT 20
#endif

void scc(int code){
    if(code < 0){
        printf("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return;
}

void *scp(void *ptr){
    if(ptr == NULL){
        printf("SDL Error: %s", SDL_GetError());
        exit(1);
    }
    return ptr;
}

Pos getRandomBoardPosition(Game *game){

    bool posFree = true;
    Pos pos = {0};
    do{
        pos = getRandomPosition();

        if(pos.x == game->food.x && pos.y == game->food.y) posFree = false;
        else posFree = true;
        
        struct Snake *currentBody = &(game->snake);
        while(posFree && currentBody){

            if (currentBody->pos.x == pos.x && currentBody->pos.y == pos.y)
                posFree = false;

            currentBody = currentBody->nextBody;
        }
    }while(!posFree);

    return pos;
}

Pos getRandomPosition(){
    int x = getRandomInt(0, BOARD_WIDTH);
    int y = getRandomInt(0, BOARD_HEIGHT);

    Pos newPosition = {x, y};
    return newPosition;
}

int getRandomInt(int min, int max) { return rand() % (max + 1 - min) + min; }