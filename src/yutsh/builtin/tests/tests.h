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
