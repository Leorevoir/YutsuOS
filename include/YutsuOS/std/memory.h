#ifndef YUTSUOS_STD_MEMORY_H
#define YUTSUOS_STD_MEMORY_H

#include <YutsuOS/std/types.h>

#define align_size(size) (((size) + 3) & ~3)

/**
 * @brief Allocates a block of memory of a given size from the heap.
 *
 * @param size The number of bytes to allocate.
 * @return A pointer to the start of the allocated block, or NULL if
 *         allocation fails. The returned pointer is aligned to a 4-byte
 *         boundary.
 */
void *allocate(const u32 size);

/**
 * @brief Frees a previously allocated block of memory.
 *
 * This function marks the block as free and attempts to merge it with
 * adjacent free blocks to reduce fragmentation.
 *
 * @param ptr A pointer to the memory block to free. If ptr is NULL,
 *            no action is taken.
 */
void liberate(void *ptr);

#endif /* YUTSUOS_STD_MEMORY_H */
