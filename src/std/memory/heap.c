#include <YutsuOS/core/heap.h>

/**
 * @file heap.c
 * @brief Kernel heap initialization and memory allocation functions.
 */

/**
 * @brief OS Kernel heap start & end
 */

extern u32 heap_start;
extern u32 heap_end;

/**
 * @brief Head of the free list.
 */

static BlockHeader *g_free_list_head = NULL;

/**
 * public
 */

void __yutsuos_core_heap_set_free_list_head(BlockHeader *head)
{
    g_free_list_head = head;
}

BlockHeader *__yutsuos_core_heap_get_free_list_head(void)
{
    return g_free_list_head;
}

/**
 * @brief Initializes the kernel heap.
 */
void __yutsuos_core_heap_init(void)
{
    g_free_list_head = (BlockHeader *)&heap_start;
    g_free_list_head->magic = YUTSUOS_CORE_HEAP_MAGIC_FREE;
    g_free_list_head->size = (u32)&heap_end - (u32)&heap_start;
    g_free_list_head->next = NULL;
}
