#ifndef YUTSUOS_STD_STRING_H
#define YUTSUOS_STD_STRING_H

#include <YutsuOS/std/types.h>

#define is_space(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r')

/**
 * @brief duplicate a null-terminated string
 * @param str pointer to the string to duplicate
 * @return pointer to the newly allocated string, or NULL on failure
 */
char *strdup(const char *str);

/**
 * @brief duplicate a string up to a maximum length
 * @param start pointer to the start of the string
 * @param len maximum length of the string to duplicate
 * @return pointer to the newly allocated string, or NULL on failure
 */
char *strndup(const char *start, u32 len);

/**
 * @brief convert an integer to a char *
 * @details the buffer must be at least 12 bytes long to hold the largest possible integer
 * @param num the integer to convert
 * @param buf the buffer to write the string to
 * @param bufsize the size of the buffer
 * @return a pointer to the start of the string within the buffer
 */
char *itoa(const i32 num, char *buf, const u32 bufsize);

/**
 * @brief fill a block of memory with a specific value
 * @param ptr pointer to the block of memory to fill
 * @param value the value to set
 * @param num number of bytes to be set to the value
 */
void *memset(void *ptr, const int value, const u32 num);

/**
 * @brief compare two blocks of memory
 * @param ptr1 pointer to the first block of memory
 * @param ptr2 pointer to the second block of memory
 * @param num number of bytes to compare
 * @return
 *   - 0 if the blocks are equal
 *   - <0 if ptr1 is less than ptr2
 *   - >0 if ptr1 is greater than ptr2
 */
i32 memcmp(const void *ptr1, const void *ptr2, const u32 num);

/**
 * @brief return the length of a null-terminated string
 * @param str the string to measure
 */
u32 strlen(const char *str);

/**
 * @brief compare two null-terminated string
 * @param s1 first string
 * @param s2 second string
 * @return
 * - 0 if the strings are equal
 * - <0 if s1 is less than s2
 * - >0 if s1 is greater than s2
 */
i32 strcmp(const char *s1, const char *s2);

/**
 * @brief compare two strings up to n characters
 * @param s1 first string
 * @param s2 second string
 * @param n maximum number of characters to compare
 * @return
 * - 0 if the strings are equal
 * - <0 if s1 is less than s2
 * - >0 if s1 is greater than s2
 */
i32 strncmp(const char *s1, const char *s2, const u32 n);

void *memcpy(void *dest, const void *src, u32 n);

#endif /* YUTSUOS_STD_STRING_H */
