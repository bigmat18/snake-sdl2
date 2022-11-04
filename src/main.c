#include <stdio.h>   
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))
#define CELL_HEIGHT ((SCREEN_HEIGHT / BOARD_HEIGHT))

#define MAX_SNAKE_MOVEMENT 0.18
#define MIN_SNAKE_MOVEMENT 0.06
#define STEP_SNAKE_MOVEMENT 0.03


// ------------------------
// STRUCT DEFINITION

typedef enum {
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
    struct Snake *nextBody;
};

typedef struct {
    Food food;
    bool quit;
    struct Snake snake;
    double gameSpeed;
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

void setSnakeState(Game *game, State newState);
void updateSnakePosition(Game *game);

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
    game->snake.state = IDLE;
    game->gameSpeed = MAX_SNAKE_MOVEMENT;
}

void initFood(Game *game) {}

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
    struct Snake *currentBody = &(game->snake);
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

    SDL_Window *const window = scp(SDL_CreateWindow("Snake Game", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE));
    SDL_Renderer *const renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

    initGame(&GAME);

    while (!GAME.quit){

        // Event handling
        SDL_Event event;

        if(SDL_PollEvent(&event)){
            
            if(event.type == SDL_QUIT)
                GAME.quit = true;

            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.scancode){
                    case SDL_SCANCODE_UP: {
                        setSnakeState(&GAME, MOVING_UP);
                        break;
                    }
                    case SDL_SCANCODE_DOWN: {
                        setSnakeState(&GAME, MOVING_DOWN);
                        break;
                    }
                    case SDL_SCANCODE_LEFT: {
                        setSnakeState(&GAME, MOVING_LEFT);
                        break;
                    }
                    case SDL_SCANCODE_RIGHT: {
                        setSnakeState(&GAME, MOVING_RIGHT);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }
        if(isSnakeMovementAllowed(&GAME))
            updateSnakePosition(&GAME);
            
        renderGame(renderer, &GAME);
    }

    return 0;
}