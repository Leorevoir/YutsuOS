#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/yutsh/builtin.h>

u8 yutsu_builtin_show(const Array *args)
{
    switch (args->size)
    {
    case 0:
        error("show: what do you want to show?????");
        return 1;
    case 1:
        show(args->data[0]);
        return 0;
    default:
        for (u32 i = 0; i < args->size; i++)
        {
            show(args->data[i]);
        }
        return YUTSUOS_SUCCESS;
    }
}
