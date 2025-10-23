#ifndef YUTSUOS_CORE_GDT_H
#define YUTSUOS_CORE_GDT_H

#include <YutsuOS/std/types.h>

#define YUTSUOS_CORE_GDT_ENTRIES 5

/**
 * @struct gdt_entry_t
 * @brief Represents a single GDT entry (segment descriptor).
 *
 * @var limit_low   Lower 16 bits of the limit.
 * @var base_low    Lower 16 bits of the base address.
 * @var base_middle Middle 8 bits of the base address.
 * @var access      Access flags, determining ring level, type, etc.
 * @var granularity Higher 4 bits of limit and granularity flags.
 * @var base_high   Higher 8 bits of the base address.
 */
typedef struct __attribute__((packed))
{
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} gdt_entry_t;

/**
 * @struct gdt_ptr_t
 * @brief Pointer structure for the GDTR register.
 *
 * @var limit The size of the GDT minus 1.
 * @var base  The linear address of the GDT.
 */
typedef struct __attribute__((packed))
{
    u16 limit;
    u32 base;
} gdt_ptr_t;

/**
 * @brief Initializes the GDT and loads it.
 */
void __yutsuos_core_gdt_init(void);

#endif /* YUTSUOS_CORE_GDT_H */
