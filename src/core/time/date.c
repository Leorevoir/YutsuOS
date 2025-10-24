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

/**
 * static helpers
 */

static inline u8 bcd_to_bin(const u8 bcd)
{
    return ((bcd / 16) * 10) + (bcd & 0x0F);
}

static inline u8 read_rtc_register(const u8 reg)
{
    __yutsuos_core_io_outb(CMOS_ADDRESS, reg);
    return __yutsuos_core_io_inb(CMOS_DATA);
}

static inline i32 is_update_in_progress(void)
{
    return read_rtc_register(RTC_STATUS_A) & 0x80;
}

static inline void get_date_from_rtc(Date *date)
{
    date->time.second = read_rtc_register(RTC_SECONDS);
    date->time.minute = read_rtc_register(RTC_MINUTES);
    date->time.hour = read_rtc_register(RTC_HOURS);
    date->day = read_rtc_register(RTC_DAY);
    date->month = read_rtc_register(RTC_MONTH);
    date->year = read_rtc_register(RTC_YEAR);
}

static inline void convert_bcd_to_binary(Date *date, const u8 register_b)
{
    if (!(register_b & 0x04))
    {
        date->time.second = bcd_to_bin(date->time.second);
        date->time.minute = bcd_to_bin(date->time.minute);
        date->time.hour =
            (((date->time.hour & 0x0F) + (((date->time.hour & 0x70) / 16) * 10)) | (date->time.hour & 0x80));
        date->day = bcd_to_bin(date->day);
        date->month = bcd_to_bin(date->month);
        date->year = bcd_to_bin(date->year);
    }
}

static inline void convert_12_to_24_hour(Date *date, const u8 register_b)
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
    wait_for(is_update_in_progress());
    get_date_from_rtc(date);

    const u8 register_b = read_rtc_register(RTC_STATUS_B);

    convert_bcd_to_binary(date, register_b);
    convert_12_to_24_hour(date, register_b);

    // TODO: handle century register
    date->year += 2000;
}
