#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>

#include <YutsuOS/std/io.h>
#include <YutsuOS/std/memory.h>
#include <YutsuOS/std/string.h>

#include "tests.h"

/**
 * static helper
 */

static inline void yutsu_builtin_tests_allocate_simple(void)
{
    show("1. Testing simple allocation (32 bytes)...\n");

    defer_liberate void *ptr1 = allocate(32);

    test_assert(ptr1 != NULL, "Allocation succeeded.", "Allocation failed.");
    test_assert(((uptr)ptr1 % 4) == 0, "Pointer is 4-byte aligned.", "Pointer is not 4-byte aligned.");

    memset(ptr1, 'A', 32);
    test_assert(memcmp(ptr1, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 32) == 0, "Memory write/read test passed.",
                "Memory write/read test failed.");
}

static inline void yutsu_builtin_tests_allocate_mid(void)
{
    show("2. Testing zero-size allocation...\n");

    defer_liberate void *ptr2 = allocate(0);

    test_assert(ptr2 == NULL, "allocate(0) returned NULL as expected.", "allocate(0) did not return NULL.");
}

static inline void yutsu_builtin_tests_allocate_hard(void)
{
    show("4. Testing multiple allocations (8, 16, 64 bytes)...\n");

    defer_liberate void *multi_ptr1 = allocate(8);
    defer_liberate void *multi_ptr2 = allocate(16);
    defer_liberate void *multi_ptr3 = allocate(64);

    test_assert(multi_ptr1 != NULL, "First allocation (8 bytes) succeeded.", "First allocation (8 bytes) failed.");
    test_assert(multi_ptr2 != NULL, "Second allocation (16 bytes) succeeded.", "Second allocation (16 bytes) failed.");
    test_assert(multi_ptr3 != NULL, "Third allocation (64 bytes) succeeded.", "Third allocation (64 bytes) failed.");
}

static inline void yutsu_builtin_tests_allocate_very_hard(void)
{
    show("5. Testing re-allocation after liberation...\n");
    defer_liberate void *realloc_ptr = allocate(32);

    test_assert(realloc_ptr != NULL, "Initial allocation of 32 bytes succeeded.",
                "Initial allocation of 32 bytes failed.");
}

/**
 * public
 */

u8 yutsu_builtin_tests_allocate(void)
{
    show("\nRunning allocation tests...\n\n");

    yutsu_builtin_tests_allocate_simple();
    yutsu_builtin_tests_allocate_mid();
    yutsu_builtin_tests_allocate_hard();
    yutsu_builtin_tests_allocate_very_hard();

    show("\nAllocation tests finished.\n");
    return YUTSUOS_SUCCESS;
}
