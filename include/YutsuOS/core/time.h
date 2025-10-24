#ifndef YUTSUOS_CORE_TIME_H
#define YUTSUOS_CORE_TIME_H

#include <YutsuOS/std/types.h>

/**
 * @struct Time
 * @brief Represents a duration of time (e.g., system uptime).
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
 * @struct TimeOfDay
 * @brief Represents a specific time of day from the RTC.
 */
typedef struct TimeOfDay
{
    u8 hour;
    u8 minute;
    u8 second;
} TimeOfDay;

/**
 * @struct Date
 * @brief Represents a specific calendar date and time from the RTC.
 */
typedef struct Date
{
    u16 year;
    u8 month;
    u8 day;
    TimeOfDay time;
} Date;

/**
 * @brief Initializes the Programmable Interval Timer (PIT).
 */
void __yutsuos_core_timer_init(void);

/**
 * @brief Get the system uptime.
 * @param uptime out parameter to store the uptime.
 */
void __yutsuos_core_get_uptime(Time *uptime);

/**
 * @brief Get the current date and time from the RTC.
 * @param date out parameter to store the date and time.
 */
void __yutsuos_core_get_date(Date *date);

#endif /* YUTSUOS_CORE_TIME_H */
