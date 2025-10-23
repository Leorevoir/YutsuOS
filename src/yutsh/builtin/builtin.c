#include <YutsuOS/macros.h>

#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

#include <YutsuOS/yutsh/builtin.h>

/**
 * static helper
 */

static const char *yutsu_builtin_commands[YUTSH_BUILTIN_COUNT] = {YUTSUOS_YUTSH_BUILTINS};
static const YutshBuiltinFunc yutsu_builtin_functions[YUTSH_BUILTIN_COUNT] = {YUTSUOS_YUTSH_BUILTIN_FUNCS};
static const char *yutsu_builtin_helps[YUTSH_BUILTIN_COUNT] = {YUTSUOS_YUTSH_BUILTIN_HELPS};

/**
 * public
 */

u8 yutsu_parse_builtin_command(const Array *args)
{
    for (u32 i = 0; i < YUTSH_BUILTIN_COUNT; ++i)
    {
        if (strcmp(args->data[0], yutsu_builtin_commands[i]) == 0)
        {
            return yutsu_builtin_functions[i](args);
        }
    }
    raise_error("Unknown command: %s", args->data[0]);
    return YUTSUOS_FAILURE;
}

u8 yutsu_builtin_help(const Array __attribute__((unused)) * args)
{
    show("Yutsu Shell Builtin Commands:\n");
    for (u32 i = 0; i < YUTSH_BUILTIN_COUNT; ++i)
    {
        show("  %s:\t \t\t%s\n", yutsu_builtin_commands[i], yutsu_builtin_helps[i]);
    }
    return YUTSUOS_SUCCESS;
}
