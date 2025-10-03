#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/kernel.h>
#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/builtin.h>

u8 yutsu_builtin_shutdown(const Array YUTSUOS_UNUSED *args)
{
    __yutsuos_core_vga_clear();
    __yutsuos_core_kernel_qemu_shutdown();
    return YUTSUOS_SUCCESS;
}
