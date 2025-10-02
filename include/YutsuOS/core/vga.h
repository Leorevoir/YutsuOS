#ifndef YUTSUOS_VGA_H
#define YUTSUOS_VGA_H

#include <YutsuOS/std/types.h>

#define YUTSUOS_VGA_ADDRESS 0xB8000

#define YUTSUOS_VGA_COLUMNS 80
#define YUTSUOS_VGA_ROWS 25

#define YUTSUOS_VGA_TAB_WIDTH 4

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

/**
 * @brief clear the screen
 * @details fills the VGA buffer with blank characters and resets the cursor position
 */
void __yutsuos_core_vga_clear(void);

/**
 * @brief put a character on the screen at the current cursor position
 * @param c the character to put
 * @param color the color attribute (foreground and background colors)
 */
void __yutsuos_core_vga_putchar(const char c, const u8 color);

/**
 * @brief put a string on the screen starting at the current cursor position
 * @param str the string to put
 * @param color the color attribute (foreground and background colors)
 */
void __yutsuos_core_vga_putstr(const char *str, const u8 color);

/**
 * @brief put a number on the screen starting at the current cursor position
 * @param num the number to put
 * @param color the color attribute (foreground and background colors)
 */
void __yutsuos_core_vga_putnbr(const i32 num, const u8 color);

/**
 * @brief move the cursor left
 */
void __yutsuos_vga_move_left(void);

/**
 * @brief move the cursor right
 */
void __yutsuos_vga_move_right(void);

/**
 * @brief move the cursor up
 */
void __yutsuos_vga_move_up(void);

/**
 * @brief move the cursor down
 */
void __yutsuos_vga_move_down(void);

#endif /* YUTSUOS_VGA_H */
