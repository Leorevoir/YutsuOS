#include <YutsuOS/std/io.h>
#include <YutsuOS/std/types.h>

#include <YutsuOS/core/vga.h>

/**
 * static helpers
 */

static inline void show_char(int **out_args, const u8 color)
{
    __yutsuos_core_vga_putchar(*(*out_args)++, color);
}

static inline void show_str(int **out_args, const u8 color)
{
    const char *str = *(const char **)(*out_args);

    __yutsuos_core_vga_putstr(str, color);
    ++(*out_args);
}

static inline void show_number(int **out_args, const u8 color)
{
    __yutsuos_core_vga_putnbr(*(*out_args)++, color);
}

static void show_dispatch(const char **out_ptr, int **out_args, const u8 color)
{
    const char specifier = **out_ptr;

    switch (specifier)
    {
    case 'c':
        show_char(out_args, color);
        break;
    case 's':
        show_str(out_args, color);
        break;
    case 'd':
        show_number(out_args, color);
        break;
    default:
        __yutsuos_core_vga_putchar('%', color);
        __yutsuos_core_vga_putchar(specifier, color);
        break;
    }

    ++(*out_ptr);
}

/**
 * public
 */

/**
 * @brief show formatted output to the TTY with color
 * @param color The color to use (use VGA color codes)
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show_color(const u8 color, const char *fmt, ...)
{
    int *args = (int *)(&fmt + 1);
    const char *p = fmt;

    while (*p)
    {
        if (*p == '%')
        {
            ++p;
            show_dispatch(&p, &args, color);
        }
        else
        {
            __yutsuos_core_vga_putchar(*p, color);
            ++p;
        }
    }
}

/**
 * @brief show formatted output to the TTY
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show(const char *fmt, ...)
{
    show_color(WHITE, fmt);
}
