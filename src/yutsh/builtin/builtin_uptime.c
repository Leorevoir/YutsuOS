#include <YutsuOS/core/time.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/yutsh/builtin.h>

static inline void show_uptime(const Time *uptime)
{
    show("Uptime: %u days, %u hours, %u minutes, %u seconds, %u milliseconds\n", uptime->days, uptime->hours,
         uptime->minutes, uptime->seconds, uptime->milliseconds);
}

u8 yutsu_builtin_uptime(const Array YUTSUOS_UNUSED *args)
{
    Time uptime;

    __yutsuos_core_get_uptime(&uptime);
    show_uptime(&uptime);
    return YUTSUOS_SUCCESS;
}
