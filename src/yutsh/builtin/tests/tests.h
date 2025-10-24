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
    YUTSH_BUILTIN_TESTS_ALLOCATE,
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
u8 yutsu_builtin_tests_allocate(void);

// clang-format off

#define YUTSUOS_YUTSH_BUILTIN_TESTS_ARGS                    \
    [YUTSH_BUILTIN_TESTS_ARG_HELP] = {                      \
        .args = "--help",                                   \
        .help = "Show this help message",                   \
        .func = yutsu_builtin_tests_help                    \
    },                                                      \
    [YUTSH_BUILTIN_TESTS_ALLOCATE] = {                      \
        .args = "--allocate",                               \
        .help = "Run allocation tests",                     \
        .func = yutsu_builtin_tests_allocate                \
    },

// clang-format on

#endif /* YUTSUOS_YUTSH_BUILTIN_TESTS_TESTS_H */
