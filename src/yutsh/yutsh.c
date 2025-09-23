#include <YutsuOS/core/vga.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>
#include <YutsuOS/yutsh/yutsh.h>

/**
 * static helpers
 */

static inline bool yutsu_shell_buffer_overflow(const char *buffer)
{
    return (strlen(buffer) >= YUTSUOS_YUTSH_MAX_BUFFER - 1);
}

/**
 * public
 */

void yutsu_shell(void)
{
    char buffer[YUTSUOS_YUTSH_MAX_BUFFER];

    for (;;)
    {
        show_color(BRIGHT_RED, "yutsh");
        show_color(BRIGHT_MAGENTA, "> ");
        input(buffer, sizeof(buffer));
        if (yutsu_shell_buffer_overflow(buffer))
        {
            raise_error("yutsu_shell buffer overflow");
            continue;
        }
    }
}
