#ifndef YUTSUOS_CORE_TIME_H
#define YUTSUOS_CORE_TIME_H

#include <YutsuOS/std/types.h>

/**
 * timers
 */

typedef struct Time
{
    u32 days;
    u32 hours;
    u32 minutes;
    u32 seconds;
    u32 milliseconds;
} Time;

/**
 * @brief initialize the system timer
 */
void __yutsuos_core_init_timer(void);

/**
 * @brief fill Time structure with the current system uptime
 */
void __yutsuos_core_get_uptime(Time *time);

#endif /* YUTSUOS_CORE_TIME_H */
