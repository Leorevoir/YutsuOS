#include <YutsuOS/core/interrupts.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

/**
 * @file idt.c
 * @brief Initialization of the Interrupt Descriptor Table (IDT).
 *
 * The IDT defines how the CPU handles interrupts and exceptions by mapping
 * interrupt vectors (0–255) to their handler routines. This file sets up
 * the IDT entries for CPU exceptions (ISRs 0–31) and hardware IRQs (32–47).
 */

/**
 * external functions
 */

/* Exception handlers (0–31) */
extern void isr0(), isr1(), isr2(), isr3(), isr4(), isr5(), isr6(), isr7();
extern void isr8(), isr9(), isr10(), isr11(), isr12(), isr13(), isr14(), isr15();
extern void isr16(), isr17(), isr18(), isr19(), isr20(), isr21(), isr22(), isr23();
extern void isr24(), isr25(), isr26(), isr27(), isr28(), isr29(), isr30(), isr31();

/* IRQ handlers (32–47) */
extern void irq0(), irq1(), irq2(), irq3(), irq4(), irq5(), irq6(), irq7();
extern void irq8(), irq9(), irq10(), irq11(), irq12(), irq13(), irq14(), irq15();

/* Assembly routine to load the IDT with lidt */
extern void __yutsuos_core_idt_load(u32);

/**
 * static global
 */
// clang-format off

static IdtEntry g_idt_entries[YUTSUOS_CORE_IDT_ENTRIES];
static IdtPtr g_idt_ptr;

static void (*g_isr_handlers[ISR_COUNT])(void) = {
    isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7, //<<< 0 -> 7
    isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15, //<<< 8 -> 15
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23, //<<< 16 -> 23
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31 //<<< 24 -> 31
};

static void (*g_irq_handlers[IRQ_COUNT])(void) = {
    irq0,  irq1,  irq2,  irq3,  irq4,  irq5,  irq6,  irq7, //<<< 0 -> 7
    irq8,  irq9,  irq10, irq11, irq12, irq13, irq14, irq15 //<<< 8 -> 15
};

// clang-format on
/**
 * static helpers
 */

/**
 * @brief Set a single IDT gate.
 */
static inline void idt_set_gate(const u8 num, const u32 base, const u16 sel, const u8 flags)
{
    IdtEntry *entry = &g_idt_entries[num];

    entry->base_lo = base & 0xFFFF;
    entry->base_hi = (base >> 16) & 0xFFFF;
    entry->sel = sel;
    entry->always0 = 0;
    entry->flags = flags;
}

/**
 * @brief Helper to batch-register IDT gates from an array of handlers.
 */
static void idt_register_range(const u8 start_vector, void (**handlers)(void), const u8 count)
{
    for (u8 i = 0; i < count; ++i)
    {
        idt_set_gate(start_vector + i, (u32)handlers[i], IDT_KERNEL_CS_SELECTOR, IDT_FLAG_PRESENT_RING0_INT_GATE);
    }
}

/**
 * public
 */

/**
 * @brief Initialize and load the Interrupt Descriptor Table (IDT).
 */
void __yutsuos_core_idt_init(void)
{
    g_idt_ptr.limit = sizeof(IdtEntry) * YUTSUOS_CORE_IDT_ENTRIES - 1;
    g_idt_ptr.base = (u32)&g_idt_entries;

    memset(g_idt_entries, 0, sizeof(g_idt_entries));

    __yutsuos_core_pic_remap();

    /* Install ISRs (CPU exceptions 0–31) */
    idt_register_range(0, g_isr_handlers, ISR_COUNT);

    /* Install IRQs (hardware interrupts 32–47) */
    idt_register_range(32, g_irq_handlers, IRQ_COUNT);

    /* Load the IDT into the CPU */
    __yutsuos_core_idt_load((u32)&g_idt_ptr);
}
