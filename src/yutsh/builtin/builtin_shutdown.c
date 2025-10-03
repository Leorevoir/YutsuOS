#include <YutsuOS/core/kernel.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

u8 yutsu_builtin_shutdown(const Array YUTSUOS_UNUSED *args)
{
    __yutsuos_core_kernel_shutdown();
    return YUTSUOS_SUCCESS;
}
