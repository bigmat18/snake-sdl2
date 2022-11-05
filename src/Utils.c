#include "headers/Render.h"
#include "headers/Utils.h"
#include "headers/Constants.h"

#include <stdbool.h>

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

        for(int i=0; i<game->snakeLength && posFree; i++){
            if (game->snake[i].pos.x == pos.x && game->snake[i].pos.y == pos.y)
                posFree = false;
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