#ifndef YUTSUOS_STD_IO_H
#define YUTSUOS_STD_IO_H

#include <YutsuOS/std/types.h>

/**
 * @brief show formatted output to the TTY
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show(const char *fmt, ...);

/**
 * @brief show formatted output to the TTY with color
 * @param color The color to use (use VGA color codes)
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show_color(const u8 color, const char *fmt, ...);

/**
 * @brief get input from the TTY
 * @param buffer The buffer to store the input
 * @param size The size of the buffer
 */
void input(char *buffer, const u32 size);

/**
 * @brief show formatted error message to the TTY in red color
 * @param fmt the format string
 * @param ... the arguments to format
 */
void error(const char *fmt, ...);

#define raise_error(...)                                                                                               \
    error(__VA_ARGS__);                                                                                                \
    show("\nby: %s:%d\n", __FILE__, __LINE__)

#endif /* YUTSUOS_STD_IO_H */
