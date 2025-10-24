#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/time.h>
#include <YutsuOS/macros.h>

/**
 * constants
 */
#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04
#define RTC_DAY 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09
#define RTC_STATUS_A 0x0A
#define RTC_STATUS_B 0x0B

#define CONVERT_BCD_HOUR_TO_BINARY(hour) (((hour & 0x0F) + (((hour & 0x70) / 16) * 10)) | (hour & 0x80))
#define BCD_TO_BINARY(value) (((value & 0x0F) + (((value & 0xF0) / 16) * 10)))

/**
 * static data
 */
static const char *g_day_names[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

/**
 * static helpers
 */

static inline u8 yutsuos_core_get_date_read_rtc_register(const u8 reg)
{
    __yutsuos_core_io_outb(CMOS_ADDRESS, reg);
    return __yutsuos_core_io_inb(CMOS_DATA);
}

static inline i32 yutsuos_core_get_date_is_update_in_progress(void)
{
    return yutsuos_core_get_date_read_rtc_register(RTC_STATUS_A) & 0x80;
}

/**
 * @brief Calculates the day of the week using Sakamoto's algorithm.
 * @param y Year
 * @param m Month
 * @param d Day
 * @return The day of the week (0 for Sunday, 1 for Monday, etc.).
 */
static u8 yutsuos_core_get_date_day_name(u16 y, u8 m, u8 d)
{
    static i32 t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    if (m < 3)
    {
        y -= 1;
    }
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

static inline void yutsuos_core_get_date_from_rtc(Date *date)
{
    date->time.second = yutsuos_core_get_date_read_rtc_register(RTC_SECONDS);
    date->time.minute = yutsuos_core_get_date_read_rtc_register(RTC_MINUTES);
    date->time.hour = yutsuos_core_get_date_read_rtc_register(RTC_HOURS);
    date->day = yutsuos_core_get_date_read_rtc_register(RTC_DAY);
    date->month = yutsuos_core_get_date_read_rtc_register(RTC_MONTH);
    date->year = yutsuos_core_get_date_read_rtc_register(RTC_YEAR);
}

static inline void yutsuos_core_get_date_BCD_TO_BINARYary(Date *date, const u8 register_b)
{
    if (!(register_b & 0x04))
    {
        date->time.second = BCD_TO_BINARY(date->time.second);
        date->time.minute = BCD_TO_BINARY(date->time.minute);
        date->time.hour = CONVERT_BCD_HOUR_TO_BINARY(date->time.hour);
        date->day = BCD_TO_BINARY(date->day);
        date->month = BCD_TO_BINARY(date->month);
        date->year = BCD_TO_BINARY(date->year);
    }
}

static inline void yutsuos_core_get_date_12_to_24_hour(Date *date, const u8 register_b)
{
    if (!(register_b & 0x02) && (date->time.hour & 0x80))
    {
        date->time.hour = ((date->time.hour & 0x7F) + 12) % 24;
    }
}

/**
 * public
 */
void __yutsuos_core_get_date(Date *date)
{
    wait_for(yutsuos_core_get_date_is_update_in_progress());
    yutsuos_core_get_date_from_rtc(date);

    const u8 register_b = yutsuos_core_get_date_read_rtc_register(RTC_STATUS_B);

    yutsuos_core_get_date_BCD_TO_BINARYary(date, register_b);
    yutsuos_core_get_date_12_to_24_hour(date, register_b);

    date->year += 2000; //<<< TODO: handle century properly

    const u8 day_index = yutsuos_core_get_date_day_name(date->year, date->month, date->day);
    date->day_name = g_day_names[day_index];
}
