#include <YutsuOS/std/io.h>
#include <YutsuOS/std/types.h>

#include <YutsuOS/core/vga.h>

/**
 * static helpers
 */

static inline void show_char(int **out_args, int color)
{
    __yutsuos_core_vga_putchar(*(*out_args)++, color);
}

static inline void show_str(int **out_args, int color)
{
    const char *str = *(const char **)(*out_args);

    __yutsuos_core_vga_putstr(str, color);
    ++(*out_args);
}

static inline void show_number(int **out_args, int color)
{
    __yutsuos_core_vga_putnbr(*(*out_args)++, color);
}

static void show_dispatch(const char **out_ptr, int **out_args)
{
    const char specifier = **out_ptr;

    switch (specifier)
    {
    case 'c':
        show_char(out_args, WHITE);
        break;
    case 's':
        show_str(out_args, WHITE);
        break;
    case 'd':
        show_number(out_args, WHITE);
        break;
    default:
        __yutsuos_core_vga_putchar('%', WHITE);
        __yutsuos_core_vga_putchar(specifier, WHITE);
        break;
    }

    ++(*out_ptr);
}

/**
 * public
 */

/**
 * @brief show formatted output to the TTY
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show(const char *fmt, ...)
{
    int *args = (int *)(&fmt + 1);
    const char *p = fmt;

    while (*p)
    {
        if (*p == '%')
        {
            ++p;
            show_dispatch(&p, &args);
        }
        else
        {
            __yutsuos_core_vga_putchar(*p, WHITE);
            ++p;
        }
    }
}
