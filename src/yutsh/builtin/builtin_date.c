#include <YutsuOS/core/time.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/yutsh/builtin.h>

static void show_date(const Date *date)
{
    show("%d-%02d-%02d %02d:%02d:%02d\n", date->year, date->month, date->day, date->time.hour, date->time.minute,
         date->time.second);
}

u8 yutsu_builtin_date(const Array YUTSUOS_UNUSED *args)
{
    Date date;

    __yutsuos_core_get_date(&date);
    show_date(&date);
    return YUTSUOS_SUCCESS;
}
