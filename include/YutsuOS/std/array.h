#ifndef YUTSUOS_STD_ARRAY_H
#define YUTSUOS_STD_ARRAY_H

#include <YutsuOS/std/types.h>

typedef struct
{
    u32 size;
    char **data;
} Array;

/**
 * @brief Parses a string into an array of arguments.
 *
 * This function splits a string by whitespace, allocating memory for an
 * array of strings and for each individual argument string.
 *
 * @param str The input string to parse.
 * @return An Array struct containing the size and data.
 */
Array array_from_string(const char *str);

/**
 * @brief Liberates the memory allocated for an Array structure.
 *
 * This function iterates through the 'data' array, freeing each individual
 * string, and then frees the 'data' array itself. It's crucial to call this
 * after you are done with an array created by array_from_string to prevent
 * memory leaks.
 *
 * @param arr A pointer to the Array to be freed.
 */
void array_free(Array *arr);

#define defer_array_free __attribute__((cleanup(array_free)))

#endif /* YUTSUOS_STD_ARRAY_H */
