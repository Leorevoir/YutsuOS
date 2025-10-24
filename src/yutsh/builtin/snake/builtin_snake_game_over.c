#include <YutsuOS/core/keyboard.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>

#include "snake.h"

/**
 * constatns
 */

#define SNAKE_GAME_OVER_MSG "GAME OVER"
#define SNAKE_GAME_OVER_PROMPT "Press any key to exit..."

/**
 * static helper
 */

static inline void yutsuos_builtin_snake_game_over_draw(void)
{
    const GameState game_state = yutsuos_builtin_snake_get_game_state();

    __yutsuos_core_vga_put_char_at((BOARD_WIDTH - sizeof(SNAKE_GAME_OVER_MSG)) / 2, BOARD_HEIGHT / 2 - 1, 0, 0);
    __yutsuos_core_vga_putstr(SNAKE_GAME_OVER_MSG, GAMEOVER_COLOR);
    show("\n\n    Final Score: %d", game_state.score);
    __yutsuos_core_vga_put_char_at((BOARD_WIDTH - sizeof(SNAKE_GAME_OVER_PROMPT)) / 2, BOARD_HEIGHT / 2 + 3, 0, 0);
    __yutsuos_core_vga_putstr(SNAKE_GAME_OVER_PROMPT, GREY);
}

/**
 *  public
 */

void yutsuos_builtin_snake_game_over(void)
{
    __yutsuos_core_vga_clear();
    yutsuos_builtin_snake_game_over_draw();

    wait_for(get_key_non_blocking());
    while (!get_key_non_blocking())
        ;
}
