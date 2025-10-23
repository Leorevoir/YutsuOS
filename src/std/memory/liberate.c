#include <YutsuOS/core/heap.h>
#include <YutsuOS/core/panic.h>

#include <YutsuOS/std/memory.h>

/**
 * public
 */

/**
 * @brief Liberates a previously allocated block of memory.
 */
void liberate(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    BlockHeader *header = (BlockHeader *)((u8 *)ptr - YUTSUOS_CORE_HEAP_HEADER_SIZE);

    if (header->magic != YUTSUOS_CORE_HEAP_MAGIC_USED)
    {
        panic("Heap corruption detected in free: invalid used block magic!");
        return;
    }

    header->magic = YUTSUOS_CORE_HEAP_MAGIC_FREE;

    // TODO: Implement merging with adjacent free blocks (coalescing) for better
    // fragmentation management

    header->next = __yutsuos_core_heap_get_free_list_head();
    __yutsuos_core_heap_set_free_list_head(header);
}
