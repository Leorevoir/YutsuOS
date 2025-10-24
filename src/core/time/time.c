#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/interrupts.h>
#include <YutsuOS/core/time.h>

#include <YutsuOS/macros.h>

/**
 * global constants
 */

#define TIMER_FREQUENCY 100
#define TIMER_BASE_FREQUENCY 1193180
#define TIMER_DIVISOR (TIMER_BASE_FREQUENCY / TIMER_FREQUENCY)

static volatile u32 g_timer_ticks = 0;

/**
 * static helpers
 */

static void yutsuos_core_timer_callback(Registers YUTSUOS_UNUSED *regs)
{
    ++g_timer_ticks;
}

/**
 * public functions
 */

void __yutsuos_core_timer_init(void)
{
    register_interrupt_handler(IRQ0, yutsuos_core_timer_callback);
    __yutsuos_core_io_outb(0x43, 0x36); //<<< command byte for square wave mode

    const u8 l = (u8)(TIMER_DIVISOR & 0xFF);
    const u8 h = (u8)((TIMER_DIVISOR >> 8) & 0xFF);

    __yutsuos_core_io_outb(0x40, l);
    __yutsuos_core_io_outb(0x40, h);
}

void __yutsuos_core_get_uptime(Time *uptime)
{
    u32 ticks;

    wait_for(ticks = g_timer_ticks);

    const u32 total_seconds = ticks / TIMER_FREQUENCY;
    const u32 total_minutes = total_seconds / 60;
    const u32 total_hours = total_minutes / 60;

    uptime->milliseconds = (ticks % TIMER_FREQUENCY) * (1000 / TIMER_FREQUENCY);
    uptime->seconds = total_seconds % 60;
    uptime->minutes = total_minutes % 60;
    uptime->hours = total_hours % 24;
    uptime->days = total_hours / 24;
}
