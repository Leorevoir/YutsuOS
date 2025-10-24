#ifndef YUTSUOS_YUTSH_BUILTIN_H
#define YUTSUOS_YUTSH_BUILTIN_H

#include <YutsuOS/std/array.h>
#include <YutsuOS/std/types.h>

// clang-format off

typedef enum : u8 {
    YUTSH_BUILTIN_SHOW = 0,
    YUTSH_BUILTIN_QWERTY,
    YUTSH_BUILTIN_AZERTY,
    YUTSH_BUILTIN_REBOOT,
    YUTSH_BUILTIN_SHUTDOWN,
    YUTSH_BUILTIN_UPTIME,
    YUTSH_BUILTIN_DATE,
    YUTSH_BUILTIN_HELP,
    YUTSH_BUILTIN_CLEAR,
    YUTSH_BUILTIN_SNAKE,
    YUTSH_BUILTIN_TESTS,
    YUTSH_BUILTIN_COUNT
} YutshBuiltins;

#define YUTSUOS_YUTSH_BUILTINS                              \
    [YUTSH_BUILTIN_SHOW]        = "show",                   \
    [YUTSH_BUILTIN_QWERTY]      = "qwerty",                 \
    [YUTSH_BUILTIN_AZERTY]      = "azerty",                 \
    [YUTSH_BUILTIN_REBOOT]      = "reboot",                 \
    [YUTSH_BUILTIN_SHUTDOWN]    = "shutdown",               \
    [YUTSH_BUILTIN_UPTIME]      = "uptime",                 \
    [YUTSH_BUILTIN_DATE]        = "date",                   \
    [YUTSH_BUILTIN_CLEAR]       = "clear",                  \
    [YUTSH_BUILTIN_SNAKE]       = "snake",                  \
    [YUTSH_BUILTIN_TESTS]       = "tests",                  \
    [YUTSH_BUILTIN_HELP]        = "help"

#define YUTSUOS_YUTSH_BUILTIN_FUNCS                         \
    [YUTSH_BUILTIN_SHOW]        = yutsu_builtin_show,       \
    [YUTSH_BUILTIN_QWERTY]      = yutsu_builtin_qwerty,     \
    [YUTSH_BUILTIN_AZERTY]      = yutsu_builtin_azerty,     \
    [YUTSH_BUILTIN_REBOOT]      = yutsu_builtin_reboot,     \
    [YUTSH_BUILTIN_SHUTDOWN]    = yutsu_builtin_shutdown,   \
    [YUTSH_BUILTIN_UPTIME]      = yutsu_builtin_uptime,     \
    [YUTSH_BUILTIN_DATE]        = yutsu_builtin_date,       \
    [YUTSH_BUILTIN_CLEAR]       = yutsu_builtin_clear,      \
    [YUTSH_BUILTIN_SNAKE]       = yutsu_builtin_snake,      \
    [YUTSH_BUILTIN_TESTS]       = yutsu_builtin_tests,      \
    [YUTSH_BUILTIN_HELP]        = yutsu_builtin_help

#define YUTSUOS_YUTSH_BUILTIN_HELPS                          \
    [YUTSH_BUILTIN_SHOW]        = "Show something",          \
    [YUTSH_BUILTIN_QWERTY]      = "Set keyboard to QWERTY",  \
    [YUTSH_BUILTIN_AZERTY]      = "Set keyboard to AZERTY",  \
    [YUTSH_BUILTIN_REBOOT]      = "Reboot the system",       \
    [YUTSH_BUILTIN_SHUTDOWN]    = "Shutdown the system",     \
    [YUTSH_BUILTIN_UPTIME]      = "Show system uptime",      \
    [YUTSH_BUILTIN_DATE]        = "Show the current date and time", \
    [YUTSH_BUILTIN_CLEAR]       = "Clear the terminal",      \
    [YUTSH_BUILTIN_SNAKE]       = "Play snake with the VGA", \
    [YUTSH_BUILTIN_TESTS]       = "Write tests --help",      \
    [YUTSH_BUILTIN_HELP]        = "Show this help message"

// clang-format on

typedef u8 (*YutshBuiltinFunc)(const Array *args);

/**
 * @brief builtin commands declarations
 */

u8 yutsu_builtin_show(const Array *args);
u8 yutsu_builtin_qwerty(const Array *args);
u8 yutsu_builtin_azerty(const Array *args);
u8 yutsu_builtin_reboot(const Array *args);
u8 yutsu_builtin_shutdown(const Array *args);
u8 yutsu_builtin_uptime(const Array *args);
u8 yutsu_builtin_date(const Array *args);
u8 yutsu_builtin_help(const Array *args);
u8 yutsu_builtin_clear(const Array *args);
u8 yutsu_builtin_snake(const Array *args);
u8 yutsu_builtin_tests(const Array *args);

/**
 * @brief getter
 */

u8 yutsu_parse_builtin_command(const Array *args);

#endif /* YUTSUOS_YUTSH_BUILTIN_H */
