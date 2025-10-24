#include <YutsuOS/core/keyboard.h>
#include <YutsuOS/core/time.h>

#include "snake.h"

/**
 * static helpers
 */

static inline void yutsuos_builtin_snake_game_handle_input_switch_input(GameState *out_state, const u8 scancode)
{
    switch (scancode)
    {
    case KEY_W:
        if (out_state->dir != DIR_DOWN)
            out_state->dir = DIR_UP;
        break;
    case KEY_S:
        if (out_state->dir != DIR_UP)
            out_state->dir = DIR_DOWN;
        break;
    case KEY_A:
        if (out_state->dir != DIR_RIGHT)
            out_state->dir = DIR_LEFT;
        break;
    case KEY_D:
        if (out_state->dir != DIR_LEFT)
            out_state->dir = DIR_RIGHT;
        break;
    case KEY_ESC:
        out_state->game_over = true;
        break;
    }
}

static void yutsuos_builtin_snake_game_handle_input(void)
{
    const u8 scancode = get_key_non_blocking();
    GameState game_state = yutsuos_builtin_snake_get_game_state();

    if (scancode == 0)
    {
        return;
    }

    yutsuos_builtin_snake_game_handle_input_switch_input(&game_state, scancode);
    yutsuos_builtin_snake_set_game_state(game_state);
}

/**
 * public
 */

void yutsuos_builtin_snake_game_loop(void)
{
    u32 last_tick = __yutsuos_core_get_ticks();

    while (!yutsuos_builtin_snake_is_game_over())
    {
        yutsuos_builtin_snake_game_handle_input();

        const u32 current_tick = __yutsuos_core_get_ticks();

        if (current_tick - last_tick > GAME_SPEED_MS / 10)
        {
            __yutsuos_core_vga_clear();
            yutsuos_builtin_snake_game_update();
            yutsuos_builtin_snake_draw();
            last_tick = current_tick;
        }
    }
}
