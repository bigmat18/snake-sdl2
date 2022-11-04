#include <stdio.h>   
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGTH 500

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))
#define CELL_HEIGHT ((SCREEN_HEIGTH / BOARD_HEIGHT))

#define FOOD_COUNT 1


// ------------------------
// STRUCT DEFINITION

typedef enum {
    DIR_RIGHT = 0,
    DIR_UP,
    DIR_LEFT,
    DIR_DOWN,
} Dir;

typedef struct {
    int x;
    int y;
} Pos, Food;

typedef struct body {
    Pos pos;
    struct body *nextBody;
} Snake;

typedef struct {
    Food food[FOOD_COUNT];
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

void initGame(Game *game);
void initSnake(Game *game);
void initFood(Game *game);

Pos getRandomBoardPosition();
Pos getRandomBoardPosition();
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

Pos getRandomBoardPosition(){
    Pos pos = getRandomPosition();
}

Pos getRandomPosition(){
    int x = getRandomInt(0, BOARD_WIDTH);
    int y = getRandomInt(0, BOARD_HEIGHT);

    Pos newPosition = {x, y};
    return newPosition;
}

int getRandomInt(int max, int min) { return (rand() % (max - min)) + min; }

// ------------------------
// GAME LOGIC FUNCTION
void initGame(Game *game) {
    game->quit = false;
}

void initSnake(Game *game) {
    game->snake.pos = getRandomBoardPosition();
    game->snake.nextBody = NULL;
}

void initFood(Game *game) {}



// ------------------------
// RENDER FUNCTION
void renderGame(SDL_Renderer *renderer, Game *game){
    render_food(renderer, game);
}

void renderFood(SDL_Renderer *renderer, Game *game){
}



// ------------------------

int main(void){
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window *const window = scp(SDL_CreateWindow("Snake Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *const renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    initGame(&GAME);

    while (!GAME.quit){

        // Event handling
        SDL_Event event;

        if(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: {
                    GAME.quit = true;
                    break;
                }
            }
        }
        
        SDL_RenderClear(renderer);

        // Update game/renderer
        scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));

        SDL_RenderPresent(renderer);
    }

    return 0;
}