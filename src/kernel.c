#include <YutsuOS/core/vga.h>

#include <YutsuOS/macros.h>

static void yutsuos_show_banner(void)
{
    yutsuos_vga_putstring(YUTSUOS_BANNER, CYAN);
}

int main(void)
{
    yutsuos_vga_clear_screen();
    yutsuos_show_banner();
    return YUTSUOS_SUCCESS;
}
