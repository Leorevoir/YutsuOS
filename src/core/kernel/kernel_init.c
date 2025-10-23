#include <YutsuOS/core/gdt.h>
#include <YutsuOS/core/heap.h>
#include <YutsuOS/core/interrupts.h>
#include <YutsuOS/core/kernel.h>
#include <YutsuOS/core/time.h>
#include <YutsuOS/core/vga.h>

#include <YutsuOS/macros.h>

/**
 * static inline
 */

static inline void yutsuos_core_kernel_init_interrupts(void)
{
    __asm__ __volatile__("sti");
}

static inline void yutsuos_core_kernel_init_core(void)
{
    __yutsuos_core_gdt_init();
    __yutsuos_core_idt_init();
    __yutsuos_core_heap_init();
    __yutsuos_core_timer_init();

    yutsuos_core_kernel_init_interrupts();
}

static inline void yutsuos_core_kernel_init_terminal(void)
{
    __yutsuos_core_vga_clear();
    __yutsuos_core_vga_putstr(YUTSUOS_BANNER, CYAN);
}

/**
 * public
 */

void __yutsuos_core_kernel_init(void)
{
    yutsuos_core_kernel_init_terminal();
    yutsuos_core_kernel_init_core();
}
