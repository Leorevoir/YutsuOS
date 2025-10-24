#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

#include "snake.h"

/**
 * public
 */

/**
 * public
 */

u8 yutsu_builtin_snake(const Array YUTSUOS_UNUSED *args)
{
    __yutsuos_core_vga_clear();

    yutsuos_builtin_snake_init_game_state();
    yutsuos_builtin_snake_game_loop();
    yutsuos_builtin_snake_game_over();

    __yutsuos_core_vga_clear();
    return YUTSUOS_SUCCESS;
}
