#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20

#define CELL_WIDTH ((SCREEN_WIDTH / BOARD_WIDTH))
#define CELL_HEIGHT ((SCREEN_HEIGHT / BOARD_HEIGHT))

#define MAX_SNAKE_MOVEMENT 0.25
#define MIN_SNAKE_MOVEMENT 0.10
#define STEP_SNAKE_MOVEMENT 0.01

#define MAX_SNAKE_LENGTH 60

#define BACKGROUND_COLOR   0x000000FF
#define SNAKE_COLOR        0x00FF00FF
#define FOOD_COLOR         0xFF0000FF
#define SCORE_COLOR        0xFFFFFF00

#define HEX_COLOR(hex)             \
    ((hex) >> (3 * 8)) & 0xFF,     \
    ((hex) >> (2 * 8)) & 0xFF,     \
    ((hex) >> (1 * 8)) & 0xFF,     \
    ((hex) >> (0 * 8)) & 0xFF

#endif
