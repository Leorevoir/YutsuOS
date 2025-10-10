// #include "YutsuOS/core/panic.h"
#include <YutsuOS/core/kernel.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/yutsh.h>

int main(void)
{
    __yutsuos_core_kernel_init();
    // panic("Kernel panic test");
    yutsu_shell();
    return YUTSUOS_SUCCESS;
}
