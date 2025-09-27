#include <YutsuOS/core/keyboard.h>
#include <YutsuOS/core/vga.h>
#include <YutsuOS/std/string.h>

/**
 * static helpers
 */

static bool g_shift_pressed = false;

/**
 * @brief get input key & handle extended codes (PS/2 Set 1)
 * @details PS/2 Set 1 uses high bit (YUTSUOS_MAX_KEYCODES) for key release, not 0xF0 prefix
 */
static inline u8 _input_get_key(bool *is_break)
{
    u8 keycode = get_key();
    *is_break = false;

    /**
     * @info in PS/2 SET 1, key release = scan code | YUTSUOS_MAX_KEYCODES
     */
    if (keycode & YUTSUOS_MAX_KEYCODES)
    {
        *is_break = true;
        keycode &= YUTSUOS_KEYBOARD_BREAK_CODE_OFFSET; ///<< remove the break bit to get base scan code
    }
    else if (keycode == YUTSUOS_KEYBOARD_EXTENDED)
    {
        u8 extended_key = get_key(); ///<< the actual key code
        if (extended_key & YUTSUOS_MAX_KEYCODES)
        {
            *is_break = true;
            extended_key &= YUTSUOS_KEYBOARD_BREAK_CODE_OFFSET;
        }
        // TODO : handle extended keys
        return 0;
    }
    return keycode;
}

static inline bool _input_handle_shift(const u8 keycode, const bool is_break)
{
    if (keycode == YUTSUOS_KEYBOARD_LEFT_SHIFT || keycode == YUTSUOS_KEYBOARD_RIGHT_SHIFT)
    {
        g_shift_pressed = !is_break;
        return true;
    }
    return false;
}

static inline bool _input_ignore_key(const bool is_break, const char c)
{
    return is_break || (c == 0);
}

static inline bool _input_build_buffer(char *buffer, const u32 size, u32 *i, const char c)
{
    if (c == '\n')
    {
        __yutsuos_core_vga_putchar('\n', WHITE);
        return true;
    }
    else if (c == '\b' && *i > 0)
    {
        --(*i);
        __yutsuos_vga_move_left();              ///<< move cursor back
        __yutsuos_core_vga_putchar(' ', WHITE); ///<< overwrite with space
        __yutsuos_vga_move_left();              ///<< move back again for next input
    }
    else if (c != '\b' && *i < size - 1) ///<< printable char, with space check
    {
        buffer[*i] = c;
        ++(*i);
        __yutsuos_core_vga_putchar(c, WHITE);
    }
    return false;
}

/**
 * public
 */

void input(char *buffer, const u32 size)
{
    u32 i = 0;

    memset(buffer, 0, size);
    while (i < size - 1)
    {
        bool is_break;
        const u8 keycode = _input_get_key(&is_break);

        if (keycode == 0)
        {
            continue;
        }

        if (_input_handle_shift(keycode, is_break))
        {
            continue;
        }

        const char c = get_char(keycode, g_shift_pressed);

        if (_input_ignore_key(is_break, c))
        {
            continue;
        }
        if (_input_build_buffer(buffer, size, &i, c))
        {
            break;
        }
    }
    buffer[i] = '\0';
}
