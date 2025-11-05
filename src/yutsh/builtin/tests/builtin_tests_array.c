#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/array.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

#include "tests.h"

/**
 * static helpers
 */

static inline void yutsu_builtin_tests_array_1(void)
{
    defer_array_free Array arr1 = array_from_string("hello world");

    test_assert(arr1.size == 2, "Array simple: size check", "Array simple: size check");
    test_assert(strcmp(arr1.data[0], "hello") == 0, "Array simple: arg 1", "Array simple: arg 1");
    test_assert(strcmp(arr1.data[1], "world") == 0, "Array simple: arg 2", "Array simple: arg 2");
}

static inline void yutsu_builtin_tests_array_2(void)
{
    defer_array_free Array arr2 = array_from_string("cmd  arg1   arg2");

    test_assert(arr2.size == 3, "Array multi-space: size check", "Array multi-space: size check");
    test_assert(strcmp(arr2.data[1], "arg1") == 0, "Array multi-space: arg 1", "Array multi-space: arg 1");
}

static inline void yutsu_builtin_tests_array_3(void)
{
    defer_array_free Array arr3 = array_from_string("  trim me  ");

    test_assert(arr3.size == 2, "Array trim: size check", "Array trim: size check");
    test_assert(strcmp(arr3.data[0], "trim") == 0, "Array trim: arg 1", "Array trim: arg 1");
    test_assert(strcmp(arr3.data[1], "me") == 0, "Array trim: arg 2", "Array trim: arg 2");
}

static inline void yutsu_builtin_tests_array_4(void)
{
    defer_array_free Array arr4 = array_from_string("");
    defer_array_free Array arr5 = array_from_string("   \t \n  ");

    test_assert(arr4.size == 0 && arr4.data == NULL, "Array empty string", "Array empty string");
    test_assert(arr5.size == 0 && arr5.data == NULL, "Array whitespace string", "Array whitespace string");
}

/**
 * public
 */

u8 yutsu_builtin_tests_array(void)
{
    show("\nRunning Array tests...\n\n");
    yutsu_builtin_tests_array_1();
    yutsu_builtin_tests_array_2();
    yutsu_builtin_tests_array_3();
    yutsu_builtin_tests_array_4();
    show("\nArray tests finished.\n");
    return YUTSUOS_SUCCESS;
}
