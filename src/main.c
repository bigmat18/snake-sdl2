#include <stdio.h>   
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGTH 500

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))
#define CELL_HEIGHT ((SCREEN_HEIGTH / BOARD_HEIGHT))


// ------------------------
// STRUCT DEFINITION

typedef enum {
    DIR_RIGHT,
    DIR_UP,
    DIR_LEFT,
    DIR_DOWN,
} Dir;

typedef struct {
    int x;
    int y;
} Pos, Food;

typedef struct Body {
    Pos pos;
    struct Body *nextBody;
} Snake;

typedef struct {
    Food food;
    bool quit;
    Snake snake;
    int gameSpeed;
    int score;
} Game;


// ------------------------
// GLOBALS VAR
Game GAME = {false};


// ------------------------
// FUNCTION DECLARATION
void scc(int code);
void *scp(void *ptr);

void renderGame(SDL_Renderer *renderer, Game *game);
void renderSnake(SDL_Renderer *renderer, Game *game);
void renderFood(SDL_Renderer *renderer, Game *game);
void renderSquare(SDL_Renderer *renderer, Pos position, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void initGame(Game *game);
void initSnake(Game *game);
void initFood(Game *game);

Pos getRandomBoardPosition(Game *game);
Pos getRandomPosition();
int getRandomInt(int max, int min);

// ------------------------
// UTILS
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
    Pos pos = getRandomPosition();
    return pos;
}

Pos getRandomPosition(){
    int x = getRandomInt(0, BOARD_WIDTH);
    int y = getRandomInt(0, BOARD_HEIGHT);

    Pos newPosition = {x, y};
    return newPosition;
}

int getRandomInt(int min, int max) { return rand() % (max + 1 - min) + min; }

// ------------------------
// GAME LOGIC FUNCTION
void initGame(Game *game) {
    game->quit = false;
    initSnake(game);
}

void initSnake(Game *game) {
    game->snake.pos = getRandomBoardPosition(game);
    game->snake.nextBody = NULL;
}

void initFood(Game *game) {}



// ------------------------
// RENDER FUNCTION
void renderGame(SDL_Renderer *renderer, Game *game){
    scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
    SDL_RenderClear(renderer);

    renderFood(renderer, game);
    renderSnake(renderer, game);

    SDL_RenderPresent(renderer);
}

void renderFood(SDL_Renderer *renderer, Game *game){}

void renderSnake(SDL_Renderer *renderer, Game *game){
    renderSquare(renderer, game->snake.pos, 0, 255, 0, 255);

    struct Body *currentBody = game->snake.nextBody;
    while(currentBody){
        renderSquare(renderer, currentBody->pos, 0, 255, 0, 255);
        currentBody = currentBody->nextBody;
    }
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

// ------------------------
int main(void){
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window *const window = scp(SDL_CreateWindow("Snake Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *const renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    initGame(&GAME);

    while (!GAME.quit){

        // Event handling
        SDL_Event event;

        if(SDL_PollEvent(&event)){
            
            if(event.type == SDL_QUIT)
                GAME.quit = true;
        }
        
        renderGame(renderer, &GAME);
    }

    return 0;
}