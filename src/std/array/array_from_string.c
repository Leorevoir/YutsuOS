#include <YutsuOS/std/array.h>
#include <YutsuOS/std/memory.h>
#include <YutsuOS/std/string.h>

#include <YutsuOS/core/panic.h>

#include <YutsuOS/macros.h>

/**
 * static helpers
 */

static inline void find_end_of_word(const char **out_str)
{
    const char *str = *out_str;

    while (*str && !is_space(*str))
    {
        ++str;
    }
    *out_str = str;
}

/**
 * @brief Counts the number of whitespace-separated arguments in a string.
 * @param str The string to scan.
 * @return The number of arguments found.
 */
static inline u32 array_count_arguments(const char *str)
{
    u32 count = 0;

    while (*str)
    {
        trim_start(str);
        if (*str)
        {
            ++count;
            find_end_of_word(&str);
        }
    }
    return count;
}

/**
 * @brief Fills the `args->data` array by parsing and duplicating each argument from the string.
 * @param args A pointer to the Array struct to populate.
 * @param str  The original input string.
 */
static inline void populate_arguments(Array *args, const char *str)
{
    const char *p = str;
    for (u32 i = 0; i < args->size; ++i)
    {
        trim_start(p);

        const char *start_of_word = p;

        find_end_of_word(&p);

        const u32 word_len = p - start_of_word;

        args->data[i] = strndup(start_of_word, word_len);
    }
    args->data[args->size] = NULL;
}

/**
 * public
 */

/**
 * @brief Parses a string into a dynamically allocated array of arguments.
 *
 * This function splits a string by whitespace, allocating memory for an
 * array of strings and for each individual argument string. The caller is
 * responsible for calling array_free() on the returned structure to prevent
 * memory leaks.
 *
 * @param str The input string to parse.
 * @return An Array struct containing the argument count and the argument vector.
 */
Array array_from_string(const char *str)
{
    if (!str || !*str)
    {
        return (Array){.size = 0, .data = NULL};
    }

    const u32 arg_count = array_count_arguments(str);
    if (arg_count == 0)
    {
        return (Array){.size = 0, .data = NULL};
    }

    Array args;
    args.size = arg_count;

    args.data = allocate(sizeof(char *) * (arg_count + 1));
    if (!args.data)
    {
        panic("Failed to allocate memory for arguments array.");
        return (Array){.size = 0, .data = NULL}; ///<< not reached
    }

    populate_arguments(&args, str);
    return args;
}
