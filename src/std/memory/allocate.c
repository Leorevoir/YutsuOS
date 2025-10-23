#include <YutsuOS/core/heap.h>
#include <YutsuOS/core/panic.h>

#include <YutsuOS/std/memory.h>

/**
 * static helpers
 */

/**
 * @brief Calculates total size including header.
 */
static inline u32 add_header_size(u32 size)
{
    return size + YUTSUOS_CORE_HEAP_HEADER_SIZE;
}

/**
 * @brief Aligns size to 4 bytes and adds header size.
 */
static inline u32 calculate_total_size(u32 size)
{
    return add_header_size(align_size(size));
}

/**
 * @brief Validates a free block's magic number.
 */
static inline void validate_free_block(BlockHeader *block)
{
    if (block->magic != YUTSUOS_CORE_HEAP_MAGIC_FREE)
    {
        panic("Heap corruption detected in allocate: invalid free block magic!");
    }
}

/**
 * @brief Checks if block is large enough for allocation.
 */
static inline bool is_block_suitable(BlockHeader *block, u32 required_size)
{
    return block->size >= required_size;
}

/**
 * @brief Calculates minimum size needed to split a block.
 */
static inline u32 min_split_size(u32 required_size)
{
    return required_size + YUTSUOS_CORE_HEAP_HEADER_SIZE + 4;
}

/**
 * @brief Checks if a block can be split after allocation.
 */
static inline bool can_split_block(u32 block_size, u32 required_size)
{
    return block_size > min_split_size(required_size);
}

/**
 * @brief Calculates the address of the new block after splitting.
 */
static inline BlockHeader *get_split_block_address(BlockHeader *block, u32 offset)
{
    return (BlockHeader *)((u8 *)block + offset);
}

/**
 * @brief Initializes a free block header.
 */
static inline void init_free_block(BlockHeader *block, u32 size, BlockHeader *next)
{
    block->magic = YUTSUOS_CORE_HEAP_MAGIC_FREE;
    block->size = size;
    block->next = next;
}

/**
 * @brief Updates block size after splitting.
 */
static inline void update_block_size(BlockHeader *block, u32 new_size)
{
    block->size = new_size;
}

/**
 * @brief Creates a new free block from the remainder of a split.
 */
static inline BlockHeader *create_remainder_block(BlockHeader *block, u32 total_size)
{
    BlockHeader *new_block = get_split_block_address(block, total_size);
    const u32 remainder_size = block->size - total_size;

    init_free_block(new_block, remainder_size, block->next);
    return new_block;
}

/**
 * @brief Splits a block into allocated and free portions.
 */
static inline BlockHeader *split_block(BlockHeader *block, u32 total_size)
{
    BlockHeader *new_block = create_remainder_block(block, total_size);

    update_block_size(block, total_size);
    return new_block;
}

/**
 * @brief Updates the free list head.
 */
static inline void set_free_list_head(BlockHeader *block)
{
    __yutsuos_core_heap_set_free_list_head(block);
}

/**
 * @brief Links previous block to next block.
 */
static inline void link_blocks(BlockHeader *prev, BlockHeader *next)
{
    prev->next = next;
}

/**
 * @brief Inserts a block into the free list.
 */
static inline void insert_into_free_list(BlockHeader *block, BlockHeader *prev)
{
    if (prev)
    {
        link_blocks(prev, block);
    }
    else
    {
        set_free_list_head(block);
    }
}

/**
 * @brief Removes a block from the free list.
 */
static inline void remove_from_free_list(BlockHeader *block, BlockHeader *prev)
{
    if (prev)
    {
        link_blocks(prev, block->next);
    }
    else
    {
        set_free_list_head(block->next);
    }
}

/**
 * @brief Marks a block as allocated.
 */
static inline void mark_block_used(BlockHeader *block)
{
    block->magic = YUTSUOS_CORE_HEAP_MAGIC_USED;
    block->next = NULL;
}

/**
 * @brief Gets pointer to user data area from block.
 */
static inline void *get_user_pointer(BlockHeader *block)
{
    return (void *)((u8 *)block + YUTSUOS_CORE_HEAP_HEADER_SIZE);
}

/**
 * @brief Marks a block as allocated and returns user pointer.
 */
static inline void *finalize_allocation(BlockHeader *block)
{
    mark_block_used(block);
    return get_user_pointer(block);
}

/**
 * @brief Handles block splitting and free list update.
 */
static inline void handle_block_split(BlockHeader *block, BlockHeader *prev, u32 total_size)
{
    BlockHeader *new_block = split_block(block, total_size);

    insert_into_free_list(new_block, prev);
}

/**
 * @brief Processes allocation from a suitable block.
 */
static inline void *allocate_from_block(BlockHeader *block, BlockHeader *prev, u32 total_size)
{
    if (can_split_block(block->size, total_size))
    {
        handle_block_split(block, prev, total_size);
    }
    else
    {
        remove_from_free_list(block, prev);
    }

    return finalize_allocation(block);
}

/**
 * @brief Gets the head of the free list.
 */
static inline BlockHeader *get_free_list_head(void)
{
    return __yutsuos_core_heap_get_free_list_head();
}

/**
 * @brief Advances to the next block in the list.
 */
static inline void advance_to_next_block(BlockHeader **current, BlockHeader **prev)
{
    *prev = *current;
    *current = (*current)->next;
}

/**
 * @brief Searches for a suitable free block.
 */
static inline BlockHeader *find_suitable_block(u32 total_size, BlockHeader **prev_out)
{
    BlockHeader *current = get_free_list_head();
    BlockHeader *prev = NULL;

    while (current)
    {
        validate_free_block(current);

        if (is_block_suitable(current, total_size))
        {
            *prev_out = prev;
            return current;
        }

        advance_to_next_block(&current, &prev);
    }

    return NULL;
}

/**
 * @brief Allocates a block of memory.
 */
void *allocate(u32 size)
{
    if (size == 0)
    {
        return NULL;
    }

    const u32 total_size = calculate_total_size(size);
    BlockHeader *prev = NULL;
    BlockHeader *block = find_suitable_block(total_size, &prev);

    if (!block)
    {
        return NULL;
    }

    return allocate_from_block(block, prev, total_size);
}
