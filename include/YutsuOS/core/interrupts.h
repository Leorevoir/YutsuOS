#ifndef YUTSUOS_CORE_INTERRUPTS_H
#define YUTSUOS_CORE_INTERRUPTS_H

#include <YutsuOS/std/types.h>

#define YUTSUOS_CORE_IDT_ENTRIES 256

/**
 * @struct Registers
 * @brief CPU state pushed onto the stack by the ISR stub.
 */
typedef struct
{
    u32 ds;                                     //<<< Data segment selector
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; //<<< Pushed by pusha
    u32 int_no, err_code;                       //<<< Interrupt number and error code
    u32 eip, cs, eflags, useresp, ss;           //<<< Pushed by the processor automatically
} Registers;

typedef void (*Isr)(Registers *);

/**
 * @brief Register an interrupt handler for a given interrupt number.
 */
void register_interrupt_handler(u8 n, Isr handler);

/**
 * @struct IdtEntry
 * @brief Represents an Interrupt Descriptor Table entry.
 */
typedef struct __attribute__((packed))
{
    u16 base_lo;
    u16 sel;
    u8 always0;
    u8 flags;
    u16 base_hi;
} IdtEntry;

/**
 * @struct IdtPtr
 * @brief Pointer structure for the IDTR register.
 */
typedef struct __attribute__((packed))
{
    u16 limit;
    u32 base;
} IdtPtr;

/**
 * @brief Initializes the IDT and loads it.
 */
void __yutsuos_core_idt_init(void);

/**
 * PIC (Programmable Interrupt Controller) related definitions
 */
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)
#define PIC_EOI 0x20

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10
#define ICW4_8086 0x01

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#define IDT_KERNEL_CS_SELECTOR 0x08

#define IDT_FLAG_PRESENT_RING0_INT_GATE 0x8E //<<< IDT gate flags: preent | ring 0 | 32-bit gate

#define ISR_COUNT 32
#define IRQ_COUNT 16

/**
 * @brief Remaps the PIC controllers.
 */
void __yutsuos_core_pic_remap(void);

#endif /* YUTSUOS_CORE_INTERRUPTS_H */
