#include <YutsuOS/macros.h>
#include <YutsuOS/std/array.h>
#include <YutsuOS/std/memory.h>
#include <YutsuOS/std/string.h>
#include <YutsuOS/std/types.h>

/**
 * static helpers
 */

/**
 * public
 */

Array array_from_string(const char *str, const char YUTSUOS_UNUSED delimiter)
{
    Array args = {.size = 0, .data = NULL};

    if (!str || !*str)
    {
        return args;
    }
    args.data[args.size] = str;
    return args;
}
