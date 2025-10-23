#include "YutsuOS/core/panic.h"
#include "YutsuOS/macros.h"
#include <YutsuOS/core/vga.h>

/**
 * show private implementation declaration
 */

void show_impl(const u8 color, const char *fmt, int *args);

/**
 * static helpers
 */

static inline void __yutsuos_core_panic_print_header(const char *file, const i32 line)
{
    __yutsuos_core_vga_putstr(YUTSUOS_CORE_PANIC_HEADER, RED);
    __yutsuos_core_vga_putstr("\nfile: ", RED);
    __yutsuos_core_vga_putstr(file, RED);
    __yutsuos_core_vga_putstr("\nline: ", RED);
    __yutsuos_core_vga_putnbr(line, RED);
    __yutsuos_core_vga_putstr("\n\nreason: ", RED);
}

static inline void __yutsuos_core_panic_print_reason(const char *reason, i32 *args)
{
    show_impl(RED, reason, args);
    __yutsuos_core_vga_putstr("\n\nSystem halted.\n", RED);
}

/**
 * public
 */

void __yutsuos_core_panic(const char *reason, const char *file, const i32 line, ...)
{
    i32 *args = (i32 *)&line + 1;

    __yutsuos_core_panic_print_header(file, line);
    __yutsuos_core_panic_print_reason(reason, args);
    forever
}
