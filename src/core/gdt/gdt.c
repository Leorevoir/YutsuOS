#include <YutsuOS/core/gdt.h>
#include <YutsuOS/std/string.h>

/**
 * GDT entries and pointer
 */
static gdt_entry_t g_gdt_entries[YUTSUOS_CORE_GDT_ENTRIES];
static gdt_ptr_t g_gdt_ptr;

/**
 * external function to load the GDT (defined in gdt_load.asm)
 */
extern void __yutsuos_core_gdt_load(u32);

/**
 * @brief Set a single GDT entry.
 * @param num The index of the entry in the GDT.
 * @param base The base address of the segment.
 * @param limit The limit of the segment.
 * @param access The access flags.
 * @param gran The granularity flags.
 */
static void yutsuos_core_gdt_set_gate(i32 num, u32 base, u32 limit, u8 access, u8 gran)
{
    g_gdt_entries[num].base_low = (base & 0xFFFF);
    g_gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    g_gdt_entries[num].base_high = (base >> 24) & 0xFF;

    g_gdt_entries[num].limit_low = (limit & 0xFFFF);
    g_gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    g_gdt_entries[num].granularity |= gran & 0xF0;
    g_gdt_entries[num].access = access;
}

/**
 * public
 */

void __yutsuos_core_gdt_init(void)
{
    g_gdt_ptr.limit = (sizeof(gdt_entry_t) * YUTSUOS_CORE_GDT_ENTRIES) - 1;
    g_gdt_ptr.base = (u32)&g_gdt_entries;

    memset(&g_gdt_entries, 0, sizeof(gdt_entry_t) * YUTSUOS_CORE_GDT_ENTRIES);

    /**
     * NULL Segment: base=0, limit=0, access=0, granularity=0
     */
    yutsuos_core_gdt_set_gate(0, 0, 0, 0, 0);

    /**
     * Kernel Code Segment: base=0, limit=4GB, ring 0, 32-bit, 4KB granularity
     */
    yutsuos_core_gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /**
     * Kernel Data Segment: base=0, limit=4GB, ring 0, 32-bit, 4KB granularity
     */
    yutsuos_core_gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /**
     * User Code Segment: base=0, limit=4GB, ring 3, 32-bit, 4KB granularity
     */
    yutsuos_core_gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    /**
     * User Data Segment: base=0, limit=4GB, ring 3, 32-bit, 4KB granularity
     */
    yutsuos_core_gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    __yutsuos_core_gdt_load((u32)&g_gdt_ptr);
}
