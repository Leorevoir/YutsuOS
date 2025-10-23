#ifndef YUTSUOS_CORE_HEAP_H
#define YUTSUOS_CORE_HEAP_H

#include <YutsuOS/std/types.h>

#define YUTSUOS_CORE_HEAP_MAGIC_USED 0xDEADBEEF
#define YUTSUOS_CORE_HEAP_MAGIC_FREE 0xCAFEBABE
#define YUTSUOS_CORE_HEAP_HEADER_SIZE sizeof(BlockHeader)

/**
 * @struct BlockHeader
 * @brief Header for each memory block in the heap.
 *
 * This header is placed just before the allocated memory block and stores
 * metadata, including a magic number for validation, its size, and a pointer
 * to the next block in the free list.
 */
typedef struct BlockHeader
{
    u32 magic;                //<<< Magic number: 0xDEADBEEF for used, 0xCAFEBABE for free
    u32 size;                 //<<< Size of the block, including the header
    struct BlockHeader *next; //<<< Pointer to the next block in the free list
} BlockHeader;

/**
 * @brief Initializes the kernel heap.
 */
void __yutsuos_core_heap_init(void);

/**
 * @brief Gets the head of the free list.
 * @return Pointer to the head of the free list.
 */
BlockHeader *__yutsuos_core_heap_get_free_list_head(void);

/**
 * @brief Sets the head of the free list.
 * @param head Ponter to the new head of the free list.
 */
void __yutsuos_core_heap_set_free_list_head(BlockHeader *head);

#endif /* YUTSUOS_CORE_HEAP_H */
