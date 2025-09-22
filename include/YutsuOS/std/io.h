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
 * @brief get input from the TTY
 * @param buffer The buffer to store the input
 * @param size The size of the buffer
 */
void input(char *buffer, const u32 size);

#endif /* YUTSUOS_STD_IO_H */
