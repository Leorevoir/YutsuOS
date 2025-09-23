#include <YutsuOS/core/vga.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>
#include <YutsuOS/yutsh/yutsh.h>

void yutsu_shell(void)
{
    char cmd[256];

    for (;;)
    {
        show_color(BRIGHT_RED, "yutsh");
        show_color(BRIGHT_MAGENTA, "> ");
        input(cmd, sizeof(cmd));

        const u32 len = strlen(cmd);

        if (len > 0 && cmd[len - 1] == '\n')
        {
            cmd[len - 1] = '\0';
        }

        if (strcmp(cmd, "clear") == 0)
        {
            show("You entered: %s\n", cmd);
            show("Length: %d\n", (i32)len);
        }
        if (strncmp(cmd, "echo ", 5) == 0)
        {
            show("You entered: %s\n", cmd);
            show("Length: %d\n", (i32)len);
        }
    }
}
