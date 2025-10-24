#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>
#include <YutsuOS/yutsh/builtin.h>

#include "tests.h"

/**
 * static constants
 */

static const BuiltinTestsArgs yutsu_builtin_tests_args[] = {YUTSUOS_YUTSH_BUILTIN_TESTS_ARGS};

/**
 * static helpers
 */

static inline void yutsu_builtin_tests_help_show(void)
{
    show("Yutsh Builtin Tests Help:\n");
    for (u8 i = 0; i < YUTSH_BUILTIN_TESTS_ARG_COUNT; i++)
    {
        show_color(BRIGHT_CYAN, "  %s", yutsu_builtin_tests_args[i].args);
        show_color(GREEN, " - %s\n", yutsu_builtin_tests_args[i].help);
    }
}

static u8 yutsu_builtin_tests_parse_arguments(const Array *args)
{
    for (u32 i = 0; i < YUTSH_BUILTIN_TESTS_ARG_COUNT; i++)
    {
        if (strcmp(args->data[1], yutsu_builtin_tests_args[i].args) == 0)
        {
            return yutsu_builtin_tests_args[i].func();
        }
    }
    return YUTSUOS_FAILURE;
}

/**
 * public
 */

u8 yutsu_builtin_tests_help(void)
{
    yutsu_builtin_tests_help_show();
    return YUTSUOS_SUCCESS;
}

u8 yutsu_builtin_tests(const Array *args)
{
    if (args->size < 2)
    {
        return YUTSUOS_FAILURE;
    }
    return yutsu_builtin_tests_parse_arguments(args);
}
