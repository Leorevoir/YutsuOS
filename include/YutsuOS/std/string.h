#ifndef YUTSUOS_STD_STRING_H
#define YUTSUOS_STD_STRING_H

#include <YutsuOS/std/types.h>

/**
 * @brief convert an integer to a char *
 * @details the buffer must be at least 12 bytes long to hold the largest possible integer
 * @param num the integer to convert
 * @param buf the buffer to write the string to
 * @param bufsize the size of the buffer
 * @return a pointer to the start of the string within the buffer
 */
char *yutsuos_itoa(const i32 num, char *buf, const u32 bufsize);

#endif /* YUTSUOS_STD_STRING_H */
