#include <YutsuOS/core/kernel.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

u8 yutsu_builtin_reboot(const Array YUTSUOS_UNUSED *args)
{
    __yutsuos_core_kernel_reboot();
    return YUTSUOS_SUCCESS;
}
