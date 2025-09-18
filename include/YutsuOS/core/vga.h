#ifndef YUTSUOS_VGA_H
#define YUTSUOS_VGA_H

#include <YutsuOS/std/types.h>

#define YUTSUOS_VGA_ADDRESS 0xB8000

#define YUTSUOS_VGA_COLUMNS 80
#define YUTSUOS_VGA_ROWS 25

#define YUTSUOS_VGA_SIZE (YUTSUOS_VGA_COLUMNS * YUTSUOS_VGA_ROWS)
#define YUTSUOS_VGA_BUFFER (YUTSUOS_VGA_COLUMNS * YUTSUOS_VGA_ROWS * 2)

#define YUTSUOS_VGA_DEFAULT_COLOR 0x0F
#define YUTSUOS_VGA_EMPTY ' '
#define YUTSUOS_VGA_BLANK (YUTSUOS_VGA_DEFAULT_COLOR << 8 | YUTSUOS_VGA_EMPTY)

enum VgaColor
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

void yutsuos_vga_clear_screen(void);

void yutsuos_vga_putchar(const char c, const u8 color);
void yutsuos_vga_putstring(const char *str, const u8 color);

#endif /* YUTSUOS_VGA_H */
