#include <YutsuOS/macros.h>

#include <YutsuOS/core/panic.h>
#include <YutsuOS/core/vga.h>

#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

#include <YutsuOS/yutsh/builtin.h>
#include <YutsuOS/yutsh/yutsh.h>

/**
 * static helpers
 */

static inline bool yutsu_shell_buffer_overflow(const char *buffer)
{
    return (strlen(buffer) >= YUTSUOS_YUTSH_MAX_BUFFER - 1);
}

static u8 yutsu_shell_execute(const char *buffer)
{
    if (!buffer || !*buffer)
    {
        return YUTSUOS_SUCCESS;
    }

    const Array args = array_from_string(buffer, ' ');

    return yutsu_parse_builtin_command(&args);
}

static inline void yutsu_shell_show_prompt(const u8 rv)
{
    show_color(BRIGHT_RED, "yutsh");

    if (rv == 0)
    {
        show_color(BRIGHT_GREEN, "> ");
    }
    else
    {
        show_color(BRIGHT_MAGENTA, "> ");
    }
}

/**
 * public
 */

void yutsu_shell(void)
{
    char buffer[YUTSUOS_YUTSH_MAX_BUFFER];
    u8 rv = YUTSUOS_SUCCESS;

    for (;;)
    {
        yutsu_shell_show_prompt(rv);
        input(buffer, sizeof(buffer));
        if (yutsu_shell_buffer_overflow(buffer))
        {
            raise_error("yutsu_shell buffer overflow");
            rv = 1;
            continue;
        }
        rv = yutsu_shell_execute(buffer);
    }
}
