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
 * @brief Initializes the Programmable Interval Timer (PIT).
 */
void __yutsuos_core_timer_init(void);

/**
 * @brief Get the system uptime.
 * @param uptime out parameter to store the uptime.
 */
void __yutsuos_core_get_uptime(Time *uptime);

#endif /* YUTSUOS_CORE_TIME_H */
