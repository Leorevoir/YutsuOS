#ifndef YUTSUOS_CORE_PANIC_H
#define YUTSUOS_CORE_PANIC_H

#define YUTSUOS_CORE_PANIC_HEADER                                                                                      \
    " /$$$$$$$                     /$$          \n"                                                                    \
    "| $$__  $$                   |__/          \n"                                                                    \
    "| $$  \\ $$ /$$$$$$  /$$$$$$$  /$$  /$$$$$$$\n"                                                                   \
    "| $$$$$$$/|____  $$| $$__  $$| $$ /$$_____/\n"                                                                    \
    "| $$____/  /$$$$$$$| $$  \\ $$| $$| $$      \n"                                                                   \
    "| $$      /$$__  $$| $$  | $$| $$| $$      \n"                                                                    \
    "| $$     |  $$$$$$$| $$  | $$| $$|  $$$$$$$\n"                                                                    \
    "|__/      \\_______/|__/  |__/|__/ \\_______/\n"                                                                  \
    "\n"

#define panic(msg, ...) __yutsuos_core_panic(msg, __FILE__, __LINE__, ##__VA_ARGS__)

void __yutsuos_core_panic(const char *msg, const char *file, int line, ...);

#endif /* YUTSUOS_CORE_PANIC_H */
