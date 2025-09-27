#include <YutsuOS/core/vga.h>
#include <YutsuOS/std/io.h>

void show_impl(const u8 color, const char *fmt, int *args);

/**
 * public
 */

void error(const char *fmt, ...)
{
    int *args = (int *)(&fmt + 1);

    show_color(RED, "ERROR: ");
    show_impl(BRIGHT_RED, fmt, args);
    show("\n");
}
