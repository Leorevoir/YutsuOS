#include <YutsuOS/core/kernel.h>
#include <YutsuOS/core/time.h>
#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>

/**
 * static helpers
 */

static inline void yutsuos_show_banner(void)
{
    __yutsuos_core_vga_putstr(YUTSUOS_BANNER, CYAN);
}

/**
 * public
 */

void __yutsuos_core_kernel_init(void)
{
    __yutsuos_core_init_timer();
    __yutsuos_core_vga_clear();
    yutsuos_show_banner();
}
