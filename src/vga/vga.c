#include <YutsuOS/types.h>
#include <YutsuOS/vga.h>

static struct
{
    u16 *buffer;
    u32 index;
} vga = {(u16 *)YUTSUOS_VGA_ADDRESS, 0};

void yutsuos_vga_clear_screen(void)
{
    const u16 blank = (YUTSUOS_VGA_DEFAULT_COLOR << 8) | ' ';

    for (u32 i = 0; i < YUTSUOS_VGA_WIDTH * YUTSUOS_VGA_HEIGHT; ++i)
    {
        vga.buffer[i] = blank;
    }
    vga.index = 0;
}
