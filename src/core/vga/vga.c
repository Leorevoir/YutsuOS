#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>

#include <YutsuOS/core/vga.h>

/**
 * private vga core struct
 */

static struct
{
    u16 *buffer;
    u32 index;
} vga = {(u16 *)YUTSUOS_VGA_ADDRESS, 0};

/**
 * static helpers
 */

/**
 * setters
 */

static void yutsuos_vga_set_cursor_position(const u16 position)
{
    yutsuos_io_outb(0x3D4, 14);
    yutsuos_io_outb(0x3D5, (position >> 8));
    yutsuos_io_outb(0x3D4, 15);
    yutsuos_io_outb(0x3D5, position);
}

static void yutsuos_vga_set_index(const u16 index)
{
    vga.index = index;
    const u32 current = vga.index;

    if (current >= YUTSUOS_VGA_SIZE)
    {
        const u16 newpos = (u16)(YUTSUOS_VGA_SIZE - YUTSUOS_VGA_COLUMNS) + (current % YUTSUOS_VGA_COLUMNS);
        yutsuos_vga_set_cursor_position(newpos);
    }
    else
    {
        yutsuos_vga_set_cursor_position((u16)current);
    }
}

/**
 * move
 */

static YUTSUOS_USED void yutsuos_vga_move_left(void)
{
    /* TODO */
}

static void yutsuos_vga_move_right(void)
{
    /* TODO */
}

static void yutsuos_vga_move_up(void)
{
    /* TODO */
}

static YUTSUOS_USED void yutsuos_vga_move_down(void)
{
    /* TODO */
}

/**
 * put
 */

static void yutsuos_vga_putnl(void)
{
    /* TODO */
}

/**
 * public functions
 */

void yutsuos_vga_putchar(const char c, const u8 color)
{
    const u32 index = vga.index;

    if (index + 1 > YUTSUOS_VGA_SIZE)
    {
        yutsuos_vga_move_up();
    }
    if (c == '\n')
    {
        yutsuos_vga_putnl();
    }
    else
    {
        yutsuos_vga_move_right();
        vga.buffer[index] = (u16)c | (u16)color << 8;
        yutsuos_vga_set_index(index + 1);
    }
}

void yutsuos_vga_clear_screen(void)
{
    const u16 blank = (YUTSUOS_VGA_DEFAULT_COLOR << 8) | ' ';

    for (u32 i = 0; i < YUTSUOS_VGA_BUFFER; ++i)
    {
        vga.buffer[i] = blank;
    }
    vga.index = 0;
}
