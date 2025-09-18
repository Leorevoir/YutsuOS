#include <YutsuOS/core/vga.h>

#include <YutsuOS/macros.h>

static void _testing_prints(void)
{
    for (char c = 'A'; c <= 'Z'; c++)
    {
        yutsuos_vga_putchar(c, YUTSUOS_VGA_DEFAULT_COLOR);
    }
    yutsuos_vga_putchar('\n', YUTSUOS_VGA_DEFAULT_COLOR);

    for (char c = 'a'; c <= 'z'; c++)
    {
        yutsuos_vga_putchar(c, YUTSUOS_VGA_DEFAULT_COLOR);
    }
    yutsuos_vga_putchar('\n', YUTSUOS_VGA_DEFAULT_COLOR);

    for (char c = '0'; c <= '9'; c++)
    {
        yutsuos_vga_putchar(c, YUTSUOS_VGA_DEFAULT_COLOR);
    }
    yutsuos_vga_putchar('\n', YUTSUOS_VGA_DEFAULT_COLOR);

    const char *symbols = "!@#$%^&*()-_=+[]{}|;:'\",.<>/?`~\\";

    for (const char *s = symbols; *s != '\0'; s++)
    {
        yutsuos_vga_putchar(*s, YUTSUOS_VGA_DEFAULT_COLOR);
    }

    yutsuos_vga_putchar('\n', YUTSUOS_VGA_DEFAULT_COLOR);
}

int main(void)
{
    yutsuos_vga_clear_screen();
    _testing_prints();
    return YUTSUOS_SUCCESS;
}
