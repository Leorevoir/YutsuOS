#ifndef YUTSUOS_MACROS_H
#define YUTSUOS_MACROS_H

#define YUTSUOS_SUCCESS 0
#define YUTSUOS_FAILURE 84

#define YUTSUOS_USED __attribute__((used))
#define YUTSUOS_UNUSED __attribute__((unused))

#define YUTSUOS_BANNER                                                                                                 \
    " /$$     /$$           /$$                         /$$$$$$   /$$$$$$\n"                                           \
    "|  $$   /$$/          | $$                        /$$__  $$ /$$__  $$\n"                                          \
    " \\  $$ /$$//$$   /$$ /$$$$$$   /$$$$$$$ /$$   /$$| $$  \\ $$| $$  \\__/\n"                                       \
    "  \\  $$$$/| $$  | $$|_  $$_/  /$$_____/| $$  | $$| $$  | $$|  $$$$$$\n"                                          \
    "   \\  $$/ | $$  | $$  | $$   |  $$$$$$ | $$  | $$| $$  | $$ \\____  $$\n"                                        \
    "    | $$  | $$  | $$  | $$ /$$\\____  $$| $$  | $$| $$  | $$ /$$  \\ $$\n"                                        \
    "    | $$  |  $$$$$$/  |  $$$$//$$$$$$$/|  $$$$$$/|  $$$$$$/|  $$$$$$/\n"                                          \
    "    |__/   \\______/    \\___/ |_______/  \\______/  \\______/  \\______/\n"                                      \
    "\n"

#define forever                                                                                                        \
    for (;;)                                                                                                           \
    {                                                                                                                  \
        __asm__ __volatile__("hlt");                                                                                   \
    }

#define wait_for(func)                                                                                                 \
    __asm__ __volatile__("cli");                                                                                       \
    (func);                                                                                                            \
    __asm__ __volatile__("sti");

#endif /* YUTSUOS_MACROS_H */
