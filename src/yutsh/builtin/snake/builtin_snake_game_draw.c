#include "snake.h"

/**
 * static helpers
 */

static inline void yutsuos_builtin_snake_draw_border(void)
{
    for (u32 x = 0; x < BOARD_WIDTH; ++x)
    {
        __yutsuos_core_vga_put_char_at(x, 0, BORDER_CHAR, BORDER_COLOR);
        __yutsuos_core_vga_put_char_at(x, BOARD_HEIGHT - 1, BORDER_CHAR, BORDER_COLOR);
    }
    for (u32 y = 0; y < BOARD_HEIGHT; ++y)
    {
        __yutsuos_core_vga_put_char_at(0, y, BORDER_CHAR, BORDER_COLOR);
        __yutsuos_core_vga_put_char_at(BOARD_WIDTH - 1, y, BORDER_CHAR, BORDER_COLOR);
    }
}

static inline void yutsuos_builtin_snake_draw_game(void)
{
    const GameState game_state = yutsuos_builtin_snake_get_game_state();

    __yutsuos_core_vga_putstr(" Score: ", SCORE_COLOR);
    __yutsuos_core_vga_putnbr(game_state.score, SCORE_COLOR);
    __yutsuos_core_vga_put_char_at(game_state.food.x, game_state.food.y, FOOD_CHAR, FOOD_COLOR);
    __yutsuos_core_vga_put_char_at(game_state.body[0].x, game_state.body[0].y, SNAKE_HEAD_CHAR, SNAKE_COLOR);
    for (u32 i = 1; i < game_state.length; ++i)
    {
        __yutsuos_core_vga_put_char_at(game_state.body[i].x, game_state.body[i].y, SNAKE_BODY_CHAR, SNAKE_COLOR);
    }
}

/**
 * public
 */

void yutsuos_builtin_snake_draw(void)
{
    yutsuos_builtin_snake_draw_border();
    yutsuos_builtin_snake_draw_game();
}
