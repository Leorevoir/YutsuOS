#include <YutsuOS/core/vga.h>
#include <YutsuOS/yutsh/yutsh.h>

#include <YutsuOS/macros.h>

static void yutsuos_show_banner(void)
{
    __yutsuos_core_vga_putstr(YUTSUOS_BANNER, CYAN);
}

int main(void)
{
    __yutsuos_core_vga_clear();
    yutsuos_show_banner();
    yutsu_shell();
    return YUTSUOS_SUCCESS;
}
