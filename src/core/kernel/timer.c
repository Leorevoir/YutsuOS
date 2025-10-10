#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/time.h>
#include <YutsuOS/std/types.h>

// TODO modularize

static inline u8 cmos_read(u8 reg)
{
    __yutsuos_core_io_outb((u16)0x70, (u8)(reg & 0x7F));

    return __yutsuos_core_io_inb((u16)0x71);
}

static void rtc_wait_update_complete(void)
{
    while (cmos_read(0x0A) & 0x80)
    {
        /* __wait__ */
    }
}

static inline u8 bcd_to_bin(u8 v)
{
    return (u8)((v & 0x0F) + ((v >> 4) * 10));
}

static u8 rtc_read_seconds(void)
{
    const u8 status_b = cmos_read(0x0B);
    const bool is_binary = (status_b & 0x04) != 0;

    rtc_wait_update_complete();

    u8 s = cmos_read(0x00);

    if (!is_binary)
        s = bcd_to_bin(s);
    return s;
}

static inline u64 rdtsc(void)
{
    u32 lo;
    u32 hi;

    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((u64)hi << 32) | (u64)lo;
}

static u64 u64_div_u32(u64 n, u32 d)
{
    const u32 hi = (u32)(n >> 32);
    const u32 lo = (u32)n;

    const u32 q_hi = hi / d;
    const u32 rem = hi % d;

    u32 q_lo;
    u32 final_rem;
    __asm__ __volatile__("divl %4" : "=a"(q_lo), "=d"(final_rem) : "a"(lo), "d"(rem), "r"(d) : "cc");

    return (((u64)q_hi) << 32) | (u64)q_lo;
}

static u32 u64_mod_u32(u64 n, u32 d)
{
    const u32 hi = (u32)(n >> 32);
    const u32 lo = (u32)n;

    const u32 rem_hi = hi % d;

    u32 final_rem;
    u32 quot; /* unused */

    __asm__ __volatile__("divl %3" : "=a"(quot), "=d"(final_rem) : "a"(lo), "r"(d), "d"(rem_hi) : "cc");
    return final_rem;
}

static volatile u64 g_boot_tsc = 0;
static volatile u32 g_tsc_per_sec = 0;
static volatile bool g_timer_ready = false;

void __yutsuos_core_init_timer(void)
{
    rtc_wait_update_complete();
    u8 s = rtc_read_seconds();
    u8 s2;

    do
    {
        s2 = rtc_read_seconds();
    } while (s2 == s);

    const u64 t1 = rdtsc();
    s = s2;

    do
    {
        s2 = rtc_read_seconds();
    } while (s2 == s);

    const u64 t2 = rdtsc();
    u64 delta = (t2 >= t1) ? (t2 - t1) : 1ULL;

    if (delta == 0)
        delta = 1ULL;

    if (delta > 0xFFFFFFFFULL)
        delta = 0xFFFFFFFFULL;

    g_tsc_per_sec = (u32)delta;
    g_boot_tsc = t2;
    g_timer_ready = true;
}

static void ms_to_time(u64 ms, Time *t)
{
    if (!t)
    {
        return;
    }

    u64 sec = u64_div_u32(ms, 1000u);
    const u32 ms_rem = u64_mod_u32(ms, 1000u);

    t->milliseconds = (u32)ms_rem;

    u64 tmp;

    /* seconds -> seconds and minutes */
    tmp = u64_div_u32(sec, 60u);               /* tmp = sec / 60 */
    const u32 sec_rem = u64_mod_u32(sec, 60u); /* sec % 60 */
    t->seconds = sec_rem;

    sec = tmp; /* sec now contains minutes */

    tmp = u64_div_u32(sec, 60u);
    u32 min_rem = u64_mod_u32(sec, 60u);
    t->minutes = min_rem;

    sec = tmp; /* sec now contains hours */

    tmp = u64_div_u32(sec, 24u);
    u32 hour_rem = u64_mod_u32(sec, 24u);
    t->hours = hour_rem;

    sec = tmp; /* sec now contains days */

    t->days = (sec > 0xFFFFFFFFULL) ? 0xFFFFFFFFu : (u32)sec;
}

void __yutsuos_core_get_uptime(Time *time)
{
    if (!time)
        return;

    if (!g_timer_ready || g_tsc_per_sec == 0)
    {
        time->days = time->hours = time->minutes = time->seconds = time->milliseconds = 0;
        return;
    }

    const u64 now = rdtsc();
    const u64 elapsed_cycles = (now >= g_boot_tsc) ? (now - g_boot_tsc) : 0ULL;

    /* elapsed_ms = (elapsed_cycles / g_tsc_per_sec) * 1000
       + ((elapsed_cycles % g_tsc_per_sec) * 1000) / g_tsc_per_sec
       Use u64_div_u32 / u64_mod_u32 where needed
    */
    const u64 sec_part = u64_div_u32(elapsed_cycles, g_tsc_per_sec);        /* whole seconds */
    const u64 rem_cycles = (u64)u64_mod_u32(elapsed_cycles, g_tsc_per_sec); /* remainder < g_tsc_per_sec */

    u64 ms = sec_part * 1000ULL;

    /* rem_ms = (rem_cycles * 1000) / g_tsc_per_sec
       rem_cycles * 1000 fits in 64-bit (rem_cycles < ~4.29e9, *1000 < ~4.29e12)
    */
    const u64 rem_mul = rem_cycles * 1000ULL;
    const u64 rem_ms = u64_div_u32(rem_mul, g_tsc_per_sec);

    ms += rem_ms;
    ms_to_time(ms, time);
}
