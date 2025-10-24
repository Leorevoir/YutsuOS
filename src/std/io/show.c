#include <YutsuOS/core/vga.h>

#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

void show_impl(const u8 color, const char *fmt, i32 *args);

/**
 * static helpers
 */

static inline void show_char(i32 **out_args, const u8 color)
{
    __yutsuos_core_vga_putchar(*(*out_args)++, color);
}

static inline void show_str(i32 **out_args, const u8 color)
{
    const char *str = *(const char **)(*out_args);

    if (str)
    {
        __yutsuos_core_vga_putstr(str, color);
    }
    else
    {
        __yutsuos_core_vga_putstr("(null)", color);
    }
    ++(*out_args);
}

static inline void show_number(i32 **out_args, const u8 color, const i32 min_width, const bool zero_pad)
{
    char buf[12];
    const i32 num = *(*out_args)++;
    const char *str = itoa(num, buf, sizeof(buf));
    const i32 len = strlen(str);

    if (zero_pad)
    {
        for (i32 i = 0; i < min_width - len; ++i)
        {
            __yutsuos_core_vga_putchar('0', color);
        }
    }
    __yutsuos_core_vga_putstr(str, color);
}

static void show_dispatch(const char **out_ptr, i32 **out_args, const u8 color)
{
    const char *p = *out_ptr;
    bool zero_pad = false;
    i32 min_width = 0;

    if (*p == '0')
    {
        zero_pad = true;
        p++;
    }

    while (*p >= '0' && *p <= '9')
    {
        min_width = min_width * 10 + (*p - '0');
        p++;
    }

    *out_ptr = p;
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
    case 'u':
        show_number(out_args, color, min_width, zero_pad);
        break;
    default:
        __yutsuos_core_vga_putchar('%', color);
        __yutsuos_core_vga_putchar(specifier, color);
        break;
    }
    ++(*out_ptr);
}

/**
 * internal implementation
 */

void show_impl(const u8 color, const char *fmt, i32 *args)
{
    const char *p = fmt;

    while (*p)
    {
        if (*p == '%')
        {
            ++p;
            if (*p == '%')
            {
                __yutsuos_core_vga_putchar('%', color);
                ++p;
            }
            else
            {
                show_dispatch(&p, &args, color);
            }
        }
        else
        {
            __yutsuos_core_vga_putchar(*p, color);
            ++p;
        }
    }
}

/**
 * public
 */

/**
 * @brief show formatted output to the TTY with color
 * @param color the color to use (use VGA color codes)
 * @param fmt the format string
 * @param ... the arguments to format
 */
void show_color(const u8 color, const char *fmt, ...)
{
    i32 *args = (i32 *)(&fmt + 1);

    show_impl(color, fmt, args);
}

/**
 * @brief show formatted output to the TTY
 * @param fmt the format string
 * @param ... the arguments to format
 */
void show(const char *fmt, ...)
{
    i32 *args = (i32 *)(&fmt + 1);

    show_impl(WHITE, fmt, args);
}
