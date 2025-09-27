#include <YutsuOS/core/panic.h>
#include <YutsuOS/core/vga.h>

/**
 * static helpers
 */

static inline void __yutsuos_core_panic_print(const char *reason, const char *file, const i32 line)
{
    __yutsuos_core_vga_putstr(YUTSUOS_CORE_PANIC_HEADER, RED);
    __yutsuos_core_vga_putstr("\nbecause: ", RED);
    __yutsuos_core_vga_putstr(reason, RED);
    __yutsuos_core_vga_putstr("\nfile: ", RED);
    __yutsuos_core_vga_putstr(file, RED);
    __yutsuos_core_vga_putstr("\nline: ", RED);
    __yutsuos_core_vga_putnbr(line, RED);
}

/**
 * public
 */

void __yutsuos_core_panic(const char *reason, const char *file, const i32 line)
{
    __yutsuos_core_vga_clear();
    __yutsuos_core_panic_print(reason, file, line);
}
