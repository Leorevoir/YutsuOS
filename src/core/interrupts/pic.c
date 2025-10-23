#include <YutsuOS/core/byte.h>
#include <YutsuOS/core/interrupts.h>

/**
 * @file pic.c
 * @brief Remaps the Programmable Interrupt Controller (PIC) to avoid conflicts
 *        between CPU exceptions and hardware IRQs.
 *
 * By default, the PICs map IRQ0–IRQ15 to vectors 0–15, which conflicts
 * with CPU exceptions (0–31). This function remaps:
 *   - Master PIC (IRQ0–IRQ7) -> vectors 32–39
 *   - Slave PIC  (IRQ8–IRQ15) -> vectors 40–47
 *
 * Also configures PICs to 8086 mode and masks/unmasks desired IRQs.
 */

/**
 * constants
 */

/* Initialization Control Words */
#define ICW1_INIT 0x10 /**< Start initialization */
#define ICW1_ICW4 0x01 /**< ICW4 will be sent */
#define ICW4_8086 0x01 /**< 8086/88 (MCS-80/85) mode */

/* Vector offsets for master and slave PICs */
#define IRQ0_VECTOR 0x20 /**< Master PIC IRQ0 maps to vector 32 */
#define IRQ8_VECTOR 0x28 /**< Slave PIC IRQ8 maps to vector 40 */

/**
 * public
 */

/**
 * @brief Remap the master and slave PICs to new interrupt vectors.
 *
 * This avoids conflicts with CPU exceptions (vectors 0–31) by moving
 * hardware IRQs to vectors 32–47.
 *
 * Also sets 8086 mode and masks all interrupts except timer (IRQ0) and
 * keyboard (IRQ1) on the master PIC. All slave IRQs are masked initially.
 */
void __yutsuos_core_pic_remap(void)
{
    /* Start initialization sequence for both PICs */
    __yutsuos_core_io_outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    __yutsuos_core_io_outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    /* Set vector offsets */
    __yutsuos_core_io_outb(PIC1_DATA, IRQ0_VECTOR); //<<< Master PIC IRQ0–IRQ7
    __yutsuos_core_io_outb(PIC2_DATA, IRQ8_VECTOR); //<<< Slave PIC IRQ8–IRQ15

    /* Configure cascading */
    __yutsuos_core_io_outb(PIC1_DATA, 0x04); //<<< Tell Master PIC there is a slave at IRQ2
    __yutsuos_core_io_outb(PIC2_DATA, 0x02); //<<< Tell Slave PIC its cascade identity

    /* Set 8086/88 (MCS-80/85) mode */
    __yutsuos_core_io_outb(PIC1_DATA, ICW4_8086);
    __yutsuos_core_io_outb(PIC2_DATA, ICW4_8086);

    /* Mask/unmask interrupts
     *   - 0 bit = enable IRQ
     *   - 1 bit = mask/disable IRQ
     * Here, enable Timer (IRQ0) and Keyboard (IRQ1), mask all others.
     */
    __yutsuos_core_io_outb(PIC1_DATA, 0xFC); //<<< 11111100: only IRQ0 & IRQ1 enabled
    __yutsuos_core_io_outb(PIC2_DATA, 0xFF); //<<< 11111111: all slave IRQs masked
}
