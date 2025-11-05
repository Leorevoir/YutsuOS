#ifndef YUTSUOS_YUTSH_BUILTIN_TESTS_TESTS_H
#define YUTSUOS_YUTSH_BUILTIN_TESTS_TESTS_H

#include <YutsuOS/std/types.h>

typedef u8 (*BuiltinTestsFunc)(void);

typedef struct BuiltinTestsArgs
{
    const char *args;
    const char *help;
    BuiltinTestsFunc func;
} BuiltinTestsArgs;

typedef enum : u8
{
    YUTSH_BUILTIN_TESTS_ARG_HELP = 0,
    YUTSH_BUILTIN_TESTS_MEMORY,
    YUTSH_BUILTIN_TESTS_STRING,
    YUTSH_BUILTIN_TESTS_ARRAY,
    YUTSH_BUILTIN_TESTS_ARG_COUNT
} YutshBuiltinTestsArgs;

/**
 * tests macros
 */

#define YUTSUOS_TEST_PASS(msg)                                                                                         \
    show_color(BRIGHT_GREEN, "[PASS]\t");                                                                              \
    show("%s\n", msg);

#define YUTSUOS_TEST_FAIL(msg)                                                                                         \
    show_color(BRIGHT_RED, "[FAIL]\t");                                                                                \
    show("%s\n", msg);

#define test_assert(cond, pass_msg, fail_msg)                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        if (cond)                                                                                                      \
        {                                                                                                              \
            YUTSUOS_TEST_PASS(pass_msg)                                                                                \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            YUTSUOS_TEST_FAIL(fail_msg)                                                                                \
        }                                                                                                              \
    } while (0)

/**
 * tests functions
 */

u8 yutsu_builtin_tests_help(void);
u8 yutsu_builtin_tests_memory(void);
u8 yutsu_builtin_tests_string(void);
u8 yutsu_builtin_tests_array(void);

// clang-format off

#define YUTSUOS_YUTSH_BUILTIN_TESTS_ARGS                    \
    [YUTSH_BUILTIN_TESTS_ARG_HELP] = {                      \
        .args = "--help",                                   \
        .help = "Show this help message",                   \
        .func = yutsu_builtin_tests_help                    \
    },                                                      \
    [YUTSH_BUILTIN_TESTS_MEMORY] = {                        \
        .args = "--memory",                                 \
        .help = "Run allocation tests",                     \
        .func = yutsu_builtin_tests_memory                  \
    },                                                      \
    [YUTSH_BUILTIN_TESTS_STRING] = {                        \
        .args = "--string",                                 \
        .help = "Run string tests",                         \
        .func = yutsu_builtin_tests_string                  \
    },                                                      \
    [YUTSH_BUILTIN_TESTS_ARRAY] = {                         \
        .args = "--array",                                  \
        .help = "Run array tests",                          \
        .func = yutsu_builtin_tests_array                   \
    },

#endif /* YUTSUOS_YUTSH_BUILTIN_TESTS_TESTS_H */
