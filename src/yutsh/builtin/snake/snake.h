#ifndef YUTSUOS_BUILTIN_SNAKE_SNAKE_H
#define YUTSUOS_BUILTIN_SNAKE_SNAKE_H

#include <YutsuOS/core/vga.h>
#include <YutsuOS/std/types.h>

/**
 * constants
 */

#define BOARD_WIDTH YUTSUOS_VGA_COLUMNS
#define BOARD_HEIGHT YUTSUOS_VGA_ROWS
#define MAX_SNAKE_LENGTH 256
#define GAME_SPEED_MS 100

#define SNAKE_HEAD_CHAR 'O'
#define SNAKE_BODY_CHAR 'o'
#define FOOD_CHAR '*'
#define BORDER_CHAR '#'

#define SNAKE_COLOR BRIGHT_GREEN
#define FOOD_COLOR BRIGHT_RED
#define BORDER_COLOR GREY
#define SCORE_COLOR CYAN
#define GAMEOVER_COLOR BRIGHT_MAGENTA

typedef enum
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct
{
    i32 x;
    i32 y;
} Vec2i;

typedef struct
{
    Vec2i body[MAX_SNAKE_LENGTH];
    u32 length;
    Direction dir;
    Vec2i food;
    u32 score;
    bool game_over;
} GameState;

void yutsuos_builtin_snake_game_loop(void);

/**
 * game state
 */

void yutsuos_builtin_snake_init_game_state(void);
void yutsuos_builtin_snake_place_food(void);
void yutsuos_builtin_snake_game_update(void);

/**
 * setter
 */
void yutsuos_builtin_snake_set_game_state(GameState state);

/**
 * getter
 */

GameState yutsuos_builtin_snake_get_game_state(void);
bool yutsuos_builtin_snake_is_game_over(void);

/**
 * game draw
 */

void yutsuos_builtin_snake_draw(void);
void yutsuos_builtin_snake_game_over(void);

#endif /* YUTSUOS_BUILTIN_SNAKE_SNAKE_H */
