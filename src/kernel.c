#include <YutsuOS/core/vga.h>

#include <YutsuOS/macros.h>

// clang-format off

static void yutsuos_neofetch(void)
{
    yutsuos_vga_putstring(
        " /$$     /$$           /$$                         /$$$$$$   /$$$$$$\n"
        "|  $$   /$$/          | $$                        /$$__  $$ /$$__  $$\n"
        " \\  $$ /$$//$$   /$$ /$$$$$$   /$$$$$$$ /$$   /$$| $$  \\ $$| $$  \\__/\n"
        "  \\  $$$$/| $$  | $$|_  $$_/  /$$_____/| $$  | $$| $$  | $$|  $$$$$$\n"
        "   \\  $$/ | $$  | $$  | $$   |  $$$$$$ | $$  | $$| $$  | $$ \\____  $$\n"
        "    | $$  | $$  | $$  | $$ /$$\\____  $$| $$  | $$| $$  | $$ /$$  \\ $$\n"
        "    | $$  |  $$$$$$/  |  $$$$//$$$$$$$/|  $$$$$$/|  $$$$$$/|  $$$$$$/\n"
        "    |__/   \\______/    \\___/ |_______/  \\______/  \\______/  \\______/\n"
        "\n", CYAN);
}

// clang-format on

int main(void)
{
    yutsuos_vga_clear_screen();
    yutsuos_neofetch();
    return YUTSUOS_SUCCESS;
}
