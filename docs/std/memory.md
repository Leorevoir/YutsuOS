# Memory

## High-level:

`memory.h` is a header defined in `std/memory.h`

the abstractions defined in the module are: `allocate()`

```c
/**
 * @brief Allocates a block of memory of a given size from the heap.
 *
 * @param size The number of bytes to allocate.
 * @return A pointer to the start of the allocated block, or NULL if
 *         allocation fails. The returned pointer is aligned to a 4-byte
 *         boundary.
 */
void *allocate(const u32 size);
```

and `liberate()`

```c
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
```

these abstractions works like `malloc()` and `free()` from the GLibC, but safer.

**usage example:**

```c
#include <YutsuOS/std/memory.h>

int main(void)
{
    void *ptr = allocate(32);

    /* ... */
    liberate(ptr);
}
```

## Low-level:

You also can _defer_ the `liberate()` at the end of the block using `defer_liberate` macro.

```c
#include <YutsuOS/std/memory.h>

int main(void)
{
    defer_liberate void *ptr = allocate(32);

    /* ... */
}
/* ptr is free'd after the block */
```
