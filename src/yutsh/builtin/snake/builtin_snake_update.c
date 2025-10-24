#include "snake.h"

/**
 * static helpers
 */

static inline void yutsuos_builtin_snake_game_update_move_body(GameState *out_state)
{
    for (u32 i = out_state->length - 1; i > 0; --i)
    {
        out_state->body[i] = out_state->body[i - 1];
    }
}

static inline void yutsuos_builtin_snake_game_update_move_head(GameState *out_state)
{
    switch (out_state->dir)
    {
    case DIR_UP:
        out_state->body[0].y--;
        break;
    case DIR_DOWN:
        out_state->body[0].y++;
        break;
    case DIR_LEFT:
        out_state->body[0].x--;
        break;
    case DIR_RIGHT:
        out_state->body[0].x++;
        break;
    }
}

static inline void yutsuos_builtin_snake_game_update_wall_collision(GameState *out_state)
{
    if (out_state->body[0].x <= 0 || out_state->body[0].x >= BOARD_WIDTH - 1 || out_state->body[0].y <= 0 ||
        out_state->body[0].y >= BOARD_HEIGHT - 1)
    {
        out_state->game_over = true;
        return;
    }
}

static inline void yutsuos_builtin_snake_game_update_self_collision(GameState *out_state)
{
    for (u32 i = 1; i < out_state->length; ++i)
    {
        if (out_state->body[0].x == out_state->body[i].x && out_state->body[0].y == out_state->body[i].y)
        {
            out_state->game_over = true;
            return;
        }
    }
}

static inline void yutsuos_builtin_snake_game_update_food_collision(GameState *out_state)
{
    const Vec2i tail = out_state->body[out_state->length - 1];

    if (out_state->body[0].x == out_state->food.x && out_state->body[0].y == out_state->food.y)
    {
        ++out_state->score;
        if (out_state->length < MAX_SNAKE_LENGTH)
        {
            ++out_state->length;
            out_state->body[out_state->length - 1] = tail;
        }
        yutsuos_builtin_snake_place_food();
    }
}

/**
 * public
 */

void yutsuos_builtin_snake_game_update(void)
{
    GameState game_state = yutsuos_builtin_snake_get_game_state();

    yutsuos_builtin_snake_game_update_move_body(&game_state);
    yutsuos_builtin_snake_game_update_move_head(&game_state);
    yutsuos_builtin_snake_game_update_wall_collision(&game_state);
    yutsuos_builtin_snake_game_update_self_collision(&game_state);
    yutsuos_builtin_snake_game_update_food_collision(&game_state);

    yutsuos_builtin_snake_set_game_state(game_state);
}
