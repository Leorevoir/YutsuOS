#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/string.h>

/**
 * @brief VGA buffer structure
 * @details each entry in the buffer is a 16-bit value where:
 * - the lower 8 bits represent the ASCII character
 * - the upper 8 bits represent the color attribute (foreground and background colors)
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

/**
 * @brief set the cursor position on the screen
 * @param position the position to set the cursor to
 */
static void yutsuos_vga_set_cursor_position(const u16 position)
{
    __yutsuos_core_io_outb(0x3D4, 14);
    __yutsuos_core_io_outb(0x3D5, (position >> 8));
    __yutsuos_core_io_outb(0x3D4, 15);
    __yutsuos_core_io_outb(0x3D5, position);
}

/**
 * @brief set the current index in the VGA buffer
 * @param index the index to set
 */
static void yutsuos_vga_set_index(const u16 index)
{
    vga.index = index;
    const u32 current = vga.index;

    if (current >= YUTSUOS_VGA_SIZE)
    {
        __yutsuos_vga_move_up();
        vga.index = (YUTSUOS_VGA_SIZE - YUTSUOS_VGA_COLUMNS) + (current % YUTSUOS_VGA_COLUMNS);
    }
    yutsuos_vga_set_cursor_position((u16)vga.index);
}

/**
 * put
 */

/**
 * @brief handle newline character
 * @details moves the cursor to the start of the next line, scrolling the screen if necessary
 */
static void yutsuos_vga_putnl(void)
{
    const u32 current_row = vga.index / YUTSUOS_VGA_COLUMNS;

    if (current_row < YUTSUOS_VGA_ROWS - 1)
    {
        yutsuos_vga_set_index((current_row + 1) * YUTSUOS_VGA_COLUMNS);
    }
    else
    {
        __yutsuos_vga_move_up();
        yutsuos_vga_set_index((YUTSUOS_VGA_ROWS - 1) * YUTSUOS_VGA_COLUMNS);
    }
}

static u16 yutsuos_vga_get_tab_spaces(void)
{
    const u16 col = vga.index % YUTSUOS_VGA_COLUMNS;
    const u16 spaces = YUTSUOS_VGA_TAB_WIDTH - (col % YUTSUOS_VGA_TAB_WIDTH);

    return spaces;
}

/**
 * public functions
 */

void __yutsuos_core_vga_put_char_at(const u32 x, const u32 y, const char c, const u8 color)
{
    if (x >= YUTSUOS_VGA_COLUMNS || y >= YUTSUOS_VGA_ROWS)
    {
        return;
    }
    const u32 index = y * YUTSUOS_VGA_COLUMNS + x;

    vga.buffer[index] = (u16)c | (u16)color << 8;
}

/**
 * move
 */

/**
 * @brief move the cursor left
 */
void __yutsuos_vga_move_left(void)
{
    if (vga.index > 0)
    {
        yutsuos_vga_set_index(vga.index - 1);
    }
}

/**
 * @brief move the cursor right
 */
void __yutsuos_vga_move_right(void)
{
    if (vga.index < YUTSUOS_VGA_SIZE - 1)
    {
        yutsuos_vga_set_index(vga.index + 1);
    }
}

/**
 * @brief move the cursor up
 */
void __yutsuos_vga_move_up(void)
{
    for (u32 i = 0; i < YUTSUOS_VGA_SIZE - YUTSUOS_VGA_COLUMNS; i++)
    {
        vga.buffer[i] = vga.buffer[i + YUTSUOS_VGA_COLUMNS];
    }
    for (u32 i = YUTSUOS_VGA_SIZE - YUTSUOS_VGA_COLUMNS; i < YUTSUOS_VGA_SIZE; i++)
    {
        vga.buffer[i] = YUTSUOS_VGA_BLANK;
    }
}

/**
 * @brief move the cursor down
 */
void __yutsuos_vga_move_down(void)
{
    const u32 current_row = vga.index / YUTSUOS_VGA_COLUMNS;

    if (current_row < YUTSUOS_VGA_ROWS - 1)
    {
        yutsuos_vga_set_index(vga.index + YUTSUOS_VGA_COLUMNS);
    }
    else
    {
        __yutsuos_vga_move_up();
        yutsuos_vga_set_index(YUTSUOS_VGA_SIZE - YUTSUOS_VGA_COLUMNS);
    }
}

/**
 * @brief put a character on the screen at the current cursor position
 * @param c the character to put
 * @param color the color attribute (foreground and background colors)
 */
void __yutsuos_core_vga_putchar(const char c, const u8 color)
{
    switch (c)
    {
    case '\n':
        yutsuos_vga_putnl();
        return;
    case '\t':
        for (u16 i = 0; i < yutsuos_vga_get_tab_spaces(); ++i)
        {
            __yutsuos_core_vga_putchar(' ', color);
        }
        return;
    case '\r':
        vga.index -= (vga.index % YUTSUOS_VGA_COLUMNS);
        yutsuos_vga_set_index(vga.index);
        return;
    default:
        break;
    }

    if (vga.index >= YUTSUOS_VGA_SIZE)
    {
        __yutsuos_vga_move_up();
        vga.index = (YUTSUOS_VGA_SIZE - YUTSUOS_VGA_COLUMNS) + (vga.index % YUTSUOS_VGA_COLUMNS);
    }

    vga.buffer[vga.index] = (u16)c | (u16)color << 8;
    __yutsuos_vga_move_right();
}

/**
 * @brief put a string on the screen starting at the current cursor position
 * @param str the string to put
 * @param color the color attribute (foreground and background colors)
 */
void __yutsuos_core_vga_putstr(const char *str, const u8 color)
{
    for (u32 i = 0; str[i] != '\0'; ++i)
    {
        __yutsuos_core_vga_putchar(str[i], color);
    }
}

/**
 * @brief put a number on the screen starting at the current cursor position
 * @param num the number to put
 * @param color the color attribute (foreground and background colors)
 */
void __yutsuos_core_vga_putnbr(const i32 num, const u8 color)
{
    char buf[12];
    const char *str = itoa(num, buf, sizeof(buf));

    __yutsuos_core_vga_putstr(str, color);
}

/**
 * @brief clear the screen
 * @details fills the VGA buffer with blank characters and resets the cursor position
 */
void __yutsuos_core_vga_clear(void)
{
    for (u32 i = 0; i < YUTSUOS_VGA_SIZE; i++)
    {
        vga.buffer[i] = YUTSUOS_VGA_BLANK;
    }
    vga.index = 0;
    yutsuos_vga_set_cursor_position(0);
}
