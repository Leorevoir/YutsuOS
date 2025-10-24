#include <YutsuOS/core/time.h>

#include "snake.h"

/**
 * static helpers
 */

static inline u32 yutsuos_builtin_snake_pseudo_rand(u32 *seed)
{
    *seed = *seed * 1103515245 + 12345;
    return (*seed / 65536) % 32768;
}

/**
 * static private global struct
 */

static GameState g_game_state;

/**
 * public
 */

void yutsuos_builtin_snake_place_food(void)
{
    u32 seed = __yutsuos_core_get_ticks();
    bool on_snake;

    do
    {
        on_snake = false;
        g_game_state.food.x = yutsuos_builtin_snake_pseudo_rand(&seed) % (BOARD_WIDTH - 2) + 1;
        g_game_state.food.y = yutsuos_builtin_snake_pseudo_rand(&seed) % (BOARD_HEIGHT - 2) + 1;

        for (u32 i = 0; i < g_game_state.length; ++i)
        {
            if (g_game_state.body[i].x == g_game_state.food.x && g_game_state.body[i].y == g_game_state.food.y)
            {
                on_snake = true;
                break;
            }
        }
    } while (on_snake);
}

void yutsuos_builtin_snake_init_game_state()
{
    g_game_state.length = 3;
    g_game_state.body[0] = (Vec2i){BOARD_WIDTH / 2, BOARD_HEIGHT / 2};
    g_game_state.body[1] = (Vec2i){BOARD_WIDTH / 2 - 1, BOARD_HEIGHT / 2};
    g_game_state.body[2] = (Vec2i){BOARD_WIDTH / 2 - 2, BOARD_HEIGHT / 2};
    g_game_state.dir = DIR_RIGHT;
    g_game_state.score = 0;
    g_game_state.game_over = false;
    yutsuos_builtin_snake_place_food();
}

void yutsuos_builtin_snake_set_game_state(GameState state)
{
    g_game_state = state;
}

GameState yutsuos_builtin_snake_get_game_state()
{
    return g_game_state;
}

bool yutsuos_builtin_snake_is_game_over(void)
{
    return g_game_state.game_over;
}
