#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/yutsh/builtin.h>

/**
 * public
 */

u8 yutsu_builtin_show(const Array *args)
{
    if (args->size < 2)
    {
        show("\n");
        return YUTSUOS_SUCCESS;
    }

    for (u32 i = 1; i < args->size; ++i)
    {
        show(args->data[i]);
        if (i < args->size - 1)
        {
            show(" ");
        }
    }
    show("\n");
    return YUTSUOS_SUCCESS;
}
