# Memory

## Description

`memory.h` is a header defined in `std/memory.h`

the abstractions defined in the module are:

- allocate()
- liberate()

## Standards

### allocate()

`allocate()` works like `malloc()` from GLibC.

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

### liberate()

`liberate()` works like `free()` from GLibC.

> [!WARNING]
> liberate can throw a panic() in some edge-cases

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

### defer macro

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
