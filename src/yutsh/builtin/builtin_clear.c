#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

/**
 * public
 */

u8 yutsu_builtin_clear(const Array __attribute__((unused)) * args)
{
    __yutsuos_core_vga_clear();
    return YUTSUOS_SUCCESS;
}
