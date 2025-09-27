#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/keyboard.h>

// clang-format off

/**
 * static helpers
 */

/**
 * @brief keymap for unshifted keys
 * @layout FR AZERTY
 * @details made using ISO-8859-1 encoding for accents like é | è
 * use \xHH for non-ASCII
 * 0 indicates no mapping or special/modifier key
 */
static const char __keymap_unshifted[YUTSUOS_MAX_KEYCODES] = {
    [KEY_NONE]          = 0,
    [KEY_ESC]           = 27,       ///<< ECHAP (Esc)
    [KEY_1]             = '&',      ///<< & (unshifted)
    [KEY_2]             = '\xE9',   ///<< é
    [KEY_3]             = '"',      ///<< "
    [KEY_4]             = '\'',     ///<< '
    [KEY_5]             = '(',      ///<< (
    [KEY_6]             = '-',      ///<< -
    [KEY_7]             = '\xE8',   ///<< è
    [KEY_8]             = '_',      ///<< _
    [KEY_9]             = '\xE7',   ///<< ç
    [KEY_0]             = '\xE0',   ///<< à
    [KEY_MINUS]         = ')',      ///<< )
    [KEY_EQUALS]        = '=',      ///<< =
    [KEY_BACKSPACE]     = '\b',     ///<< RET.ARR (Backspace)
    [KEY_TAB]           = '\t',     ///<< TAB
    [KEY_Q]             = 'a',      ///<< a
    [KEY_W]             = 'z',      ///<< z
    [KEY_E]             = 'e',      ///<< e
    [KEY_R]             = 'r',      ///<< r
    [KEY_T]             = 't',      ///<< t
    [KEY_Y]             = 'y',      ///<< y
    [KEY_U]             = 'u',      ///<< u
    [KEY_I]             = 'i',      ///<< i
    [KEY_O]             = 'o',      ///<< o
    [KEY_P]             = 'p',      ///<< p
    [KEY_LEFT_BRACKET]  = '^',      ///<< ACCENT CIRCONFLEXE (^ unshifted)
    [KEY_RIGHT_BRACKET] = '$',      ///<< $
    [KEY_ENTER]         = '\n',     ///<< ENTREE (Enter)
    [KEY_LEFT_CTRL]     = 0,        ///<< CTRL
    [KEY_A]             = 'q',      ///<< q
    [KEY_S]             = 's',      ///<< s
    [KEY_D]             = 'd',      ///<< d
    [KEY_F]             = 'f',      ///<< f
    [KEY_G]             = 'g',      ///<< g
    [KEY_H]             = 'h',      ///<< h
    [KEY_J]             = 'j',      ///<< j
    [KEY_K]             = 'k',      ///<< k
    [KEY_L]             = 'l',      ///<< l
    [KEY_SEMICOLON]     = 'm',      ///<< m
    [KEY_SINGLE_QUOTE]  = '\xF9',   ///<< ù
    [KEY_GRAVE]         = '\xB2',   ///<< ² (superscript 2)
    [KEY_LEFT_SHIFT]    = 0,        ///<< MAJ (Shift)
    [KEY_BACKSLASH]     = '*',      ///<< *
    [KEY_Z]             = 'w',      ///<< w
    [KEY_X]             = 'x',      ///<< x
    [KEY_C]             = 'c',      ///<< c
    [KEY_V]             = 'v',      ///<< v
    [KEY_B]             = 'b',      ///<< b
    [KEY_N]             = 'n',      ///<< n
    [KEY_M]             = ',',      ///<< ,
    [KEY_COMMA]         = ';',      ///<< ;
    [KEY_PERIOD]        = ':',      ///<< :
    [KEY_SLASH]         = '!',      ///<< !
    [KEY_RIGHT_SHIFT]   = 0,        ///<< MAJ DROITE (Right Shift)
    [KEY_KP_MULTIPLY]   = '*',      ///<< * (numpad, unchanged)
    [KEY_LEFT_ALT]      = 0,        ///<< ALT
    [KEY_SPACE]         = ' ',      ///<< ESPACE (Space)
    [KEY_CAPS_LOCK]     = 0,        ///<< VERR.MAJ (Caps Lock)
    [KEY_F1]            = 0,
    [KEY_F2]            = 0,
    [KEY_F3]            = 0,
    [KEY_F4]            = 0,
    [KEY_F5]            = 0,
    [KEY_F6]            = 0,
    [KEY_F7]            = 0,
    [KEY_F8]            = 0,
    [KEY_F9]            = 0,
    [KEY_F10]           = 0,
    [KEY_NUM_LOCK]      = 0,
    [KEY_SCROLL_LOCK]   = 0,
    [KEY_KP_7]          = '7',
    [KEY_KP_8]          = '8',
    [KEY_KP_9]          = '9',
    [KEY_KP_MINUS]      = '-',
    [KEY_KP_4]          = '4',
    [KEY_KP_5]          = '5',
    [KEY_KP_6]          = '6',
    [KEY_KP_PLUS]       = '+',
    [KEY_KP_1]          = '1',
    [KEY_KP_2]          = '2',
    [KEY_KP_3]          = '3',
    [KEY_KP_0]          = '0',
    [KEY_KP_PERIOD]     = '.',
    [0x56]              = '<',
};

/**
 * @brief keymap for shifted keys
 * @layout FR AZERTY
 * @details made using ISO-8859-1 encoding
 * use \xHH for non-ASCII
 * 0 indicates no mapping or special/modifier key
 */
static const char __keymap_shifted[YUTSUOS_MAX_KEYCODES] = {
    [KEY_NONE]          = 0,
    [KEY_ESC]           = 27,
    [KEY_1]             = '1',
    [KEY_2]             = '2',
    [KEY_3]             = '3',
    [KEY_4]             = '4',
    [KEY_5]             = '5',
    [KEY_6]             = '6',
    [KEY_7]             = '7',
    [KEY_8]             = '8',
    [KEY_9]             = '9',
    [KEY_0]             = '0',
    [KEY_MINUS]         = '\xB0',   ///<< °
    [KEY_EQUALS]        = '+',
    [KEY_BACKSPACE]     = '\b',
    [KEY_TAB]           = '\t',
    [KEY_Q]             = 'A',
    [KEY_W]             = 'Z',
    [KEY_E]             = 'E',
    [KEY_R]             = 'R',
    [KEY_T]             = 'T',
    [KEY_Y]             = 'Y',
    [KEY_U]             = 'U',
    [KEY_I]             = 'I',
    [KEY_O]             = 'O',
    [KEY_P]             = 'P',
    [KEY_LEFT_BRACKET]  = '\xA8',   ///<< ¨ (diaeresis)
    [KEY_RIGHT_BRACKET] = '\xA3',   ///<< £
    [KEY_ENTER]         = '\n',
    [KEY_LEFT_CTRL]     = 0,
    [KEY_A]             = 'Q',
    [KEY_S]             = 'S',
    [KEY_D]             = 'D',
    [KEY_F]             = 'F',
    [KEY_G]             = 'G',
    [KEY_H]             = 'H',
    [KEY_J]             = 'J',
    [KEY_K]             = 'K',
    [KEY_L]             = 'L',
    [KEY_SEMICOLON]     = 'M',
    [KEY_SINGLE_QUOTE]  = '%',
    [KEY_GRAVE]         = '~',      ///<< often ~ for shifted ²
    [KEY_LEFT_SHIFT]    = 0,
    [KEY_BACKSLASH]     = '\xB5',   ///<< µ
    [KEY_Z]             = 'W',
    [KEY_X]             = 'X',
    [KEY_C]             = 'C',
    [KEY_V]             = 'V',
    [KEY_B]             = 'B',
    [KEY_N]             = 'N',
    [KEY_M]             = '?',
    [KEY_COMMA]         = '.',
    [KEY_PERIOD]        = '/',
    [KEY_SLASH]         = '\xA7',   ///<< §
    [KEY_RIGHT_SHIFT]   = 0,
    [KEY_KP_MULTIPLY]   = '*',
    [KEY_LEFT_ALT]      = 0,
    [KEY_SPACE]         = ' ',
    [KEY_CAPS_LOCK]     = 0,
    [KEY_F1]            = 0,
    [KEY_F2]            = 0,
    [KEY_F3]            = 0,
    [KEY_F4]            = 0,
    [KEY_F5]            = 0,
    [KEY_F6]            = 0,
    [KEY_F7]            = 0,
    [KEY_F8]            = 0,
    [KEY_F9]            = 0,
    [KEY_F10]           = 0,
    [KEY_NUM_LOCK]      = 0,
    [KEY_SCROLL_LOCK]   = 0,
    [KEY_KP_7]          = '7',
    [KEY_KP_8]          = '8',
    [KEY_KP_9]          = '9',
    [KEY_KP_MINUS]      = '-',
    [KEY_KP_4]          = '4',
    [KEY_KP_5]          = '5',
    [KEY_KP_6]          = '6',
    [KEY_KP_PLUS]       = '+',
    [KEY_KP_1]          = '1',
    [KEY_KP_2]          = '2',
    [KEY_KP_3]          = '3',
    [KEY_KP_0]          = '0',
    [KEY_KP_PERIOD]     = '.',
    [0x56]              = '>',
};

// clang-format on

/**
 * @brief read a scan code from the PS/2 keyboard controller (port 0x60)
 * @return raw scan code (u8).
 */
u8 get_key(void)
{
    /**
     * @info wait until a key is available
     */
    while (!(__yutsuos_core_io_inb(YUTSUOS_STATUS_PORT) & YUTSUOS_STATUS_BUFFER_FULL))
    {
        __asm__ __volatile__("nop");
    }
    return __yutsuos_core_io_inb(0x60);
}

/**
 * @brief get an ASCII char from the u8 PS/2 keycode
 * @details supports basic FR AZERY layout
 * TODO: support for other layouts like US QWERTY
 *
 * @param keycode the scan code to convert.
 * @param shift true if shift is pressed, false otherwise.
 * @return corresponding ASCII char | 0 if none.
 */
char get_char(const u8 keycode, bool shift)
{
    if (keycode >= YUTSUOS_MAX_KEYCODES)
    {
        return 0;
    }
    return shift ? __keymap_shifted[keycode] : __keymap_unshifted[keycode];
}
