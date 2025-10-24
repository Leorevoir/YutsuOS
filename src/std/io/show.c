#include <YutsuOS/core/vga.h>

#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

void show_impl(const u8 color, const char *fmt, i32 *args);

/**
 * subflags struct
 */

typedef struct
{
    bool left_justify; //<<< a '-' flag was present
    bool zero_pad;     //<<< a '0' flag was present
    i32 min_width;     //<<< minimum width of the output
} ShowFormatFlags;

/**
 * @brief Prints padding characters to the screen.
 * @param pad_char The character to use for padding (' ' or '0').
 * @param count The number of padding characters to print.
 * @param color The VGA color for the characters.
 */
static inline void show_padding(char pad_char, i32 count, const u8 color)
{
    for (i32 i = 0; i < count; ++i)
    {
        __yutsuos_core_vga_putchar(pad_char, color);
    }
}

/**
 * @brief Parses the format flags (like '0', '-', width) from a format string.
 * @param fmt_ptr A pointer to the current position in the format string. This pointer is advanced past the flags.
 * @return A ShowFormatFlags struct populated with the parsed options.
 */
static ShowFormatFlags parse_format_flags(const char **fmt_ptr)
{
    ShowFormatFlags flags = {
        .left_justify = false,
        .zero_pad = false,
        .min_width = 0,
    };

    const char *p = *fmt_ptr;

    bool parsing_flags = true;
    while (parsing_flags)
    {
        switch (*p)
        {
        case '-':
            flags.left_justify = true;
            p++;
            break;
        case '0':
            if (!flags.left_justify)
            {
                flags.zero_pad = true;
            }
            p++;
            break;
        default:
            parsing_flags = false;
            break;
        }
    }

    while (*p >= '0' && *p <= '9')
    {
        flags.min_width = flags.min_width * 10 + (*p - '0');
        p++;
    }

    *fmt_ptr = p;
    return flags;
}

/**
 * @brief Prints a character with respect to format flags (not very useful for chars, but here for consistency).
 */
static inline void show_char(i32 **out_args, const u8 color, const ShowFormatFlags *flags)
{
    if (!flags->left_justify)
    {
        show_padding(' ', flags->min_width - 1, color);
    }

    __yutsuos_core_vga_putchar(*(*out_args)++, color);

    if (flags->left_justify)
    {
        show_padding(' ', flags->min_width - 1, color);
    }
}

/**
 * @brief Prints a string, applying formatting flags for width and justification.
 */
static inline void show_str(i32 **out_args, const u8 color, const ShowFormatFlags *flags)
{
    const char *str = *(const char **)(*out_args);

    if (!str)
    {
        str = "(null)";
    }
    ++(*out_args);

    const i32 len = strlen(str);
    const i32 padding = flags->min_width - len;

    if (!flags->left_justify)
    {
        show_padding(' ', padding, color);
    }

    __yutsuos_core_vga_putstr(str, color);

    if (flags->left_justify)
    {
        show_padding(' ', padding, color);
    }
}

/**
 * @brief Prints a number, applying formatting flags for width, justification, and zero-padding.
 */
static inline void show_number(i32 **out_args, const u8 color, const ShowFormatFlags *flags)
{
    char buf[12];
    const i32 num = *(*out_args)++;
    const char *str = itoa(num, buf, sizeof(buf));
    const i32 len = strlen(str);

    const i32 padding = flags->min_width - len;
    const char pad_char = flags->zero_pad ? '0' : ' ';

    if (!flags->left_justify)
    {
        show_padding(pad_char, padding, color);
    }

    __yutsuos_core_vga_putstr(str, color);

    if (flags->left_justify)
    {
        show_padding(' ', padding, color);
    }
}

/**
 * @brief Parses a format specifier, gets flags, and dispatches to the correct handler.
 * @param out_ptr A pointer to the current position in the format string. It's advanced past the specifier.
 * @param out_args A pointer to the current argument in the variadic list.
 * @param color The VGA color to use for printing.
 */
static void show_formatted_arg(const char **out_ptr, i32 **out_args, const u8 color)
{
    ShowFormatFlags flags = parse_format_flags(out_ptr);
    const char specifier = **out_ptr;

    switch (specifier)
    {
    case 'c':
        show_char(out_args, color, &flags);
        break;
    case 's':
        show_str(out_args, color, &flags);
        break;
    case 'd':
    case 'u':
        show_number(out_args, color, &flags);
        break;
    default:
        __yutsuos_core_vga_putchar('%', color);
        if (flags.zero_pad)
            __yutsuos_core_vga_putchar('0', color);
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
                show_formatted_arg(&p, &args, color);
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

void show_color(const u8 color, const char *fmt, ...)
{
    i32 *args = (i32 *)(&fmt + 1);

    show_impl(color, fmt, args);
}

void show(const char *fmt, ...)
{
    i32 *args = (i32 *)(&fmt + 1);

    show_impl(WHITE, fmt, args);
}
