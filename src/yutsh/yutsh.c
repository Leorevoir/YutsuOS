#include <YutsuOS/core/vga.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>
#include <YutsuOS/yutsh/yutsh.h>

void yutsu_shell(void)
{
    char cmd[256];

    for (;;)
    {
        show("yutsu> ");
        input(cmd, sizeof(cmd));

        const u32 len = strlen(cmd); ///<< trim newline

        if (len > 0 && cmd[len - 1] == '\n')
        {
            cmd[len - 1] = '\0';
        }

        /* test commands */
        if (strcmp(cmd, "help") == 0)
        {
            show("Available commands:\n");
            show("  help - Show this help\n");
            show("  clear - Clear screen\n");
            show("  echo [text] - Echo back text\n");
            show("  halt - Halt the CPU\n");
        }
        else if (strcmp(cmd, "clear") == 0)
        {
            __yutsuos_core_vga_clear();
        }
        else if (strncmp(cmd, "echo ", 5) == 0)
        {
            show("%s\n", cmd + 5);
        }
        else if (strcmp(cmd, "halt") == 0)
        {
            asm volatile("cli; hlt");
        }
        else if (cmd[0] != '\0')
        {
            show("Unknown command: %s\n", cmd);
        }
    }
}
