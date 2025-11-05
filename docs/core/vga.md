# vga

## High-level:

`core/vga.h` is a core header for abstractions used to interact with the _VGA buffer_.

```c
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
void__yutsuos_core_vga_putchar(const char c, const u8 color);

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

/**
 * @brief put a character on the screen at a specific (x, y) position.
 * @param x the column
 * @param y the row
 * @param c the character to put
 * @param color the color attribute
 */
void __yutsuos_core_vga_put_char_at(const u32 x, const u32 y, const char c, const u8 color);
```

## Low-level

the _VGA buffer_ structure is a private anonyme static structure defined in `core/vga/vga.c`.

```c
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
```

as the _VGA buffer_ is a core critical feature, the only way to access | modify this structure is by using the functions abstractions defined in the header.

It is also the module responsible for the cursor movements.
