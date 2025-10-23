#include <YutsuOS/core/kernel.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/yutsh/yutsh.h>

int main(void)
{
    __yutsuos_core_kernel_init();
    yutsu_shell();
    return YUTSUOS_SUCCESS;
}
