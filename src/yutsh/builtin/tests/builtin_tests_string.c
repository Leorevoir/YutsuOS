#include <YutsuOS/core/vga.h>
#include <YutsuOS/macros.h>
#include <YutsuOS/std/io.h>
#include <YutsuOS/std/string.h>

#include "tests.h"

/**
 * static helpers
 */

static inline void yutsu_builtin_tests_strlen(void)
{
    test_assert(strlen("") == 0, "strlen(\"\")", "strlen(\"\")");
    test_assert(strlen("hello") == 5, "strlen(\"hello\")", "strlen(\"hello\")");
    test_assert(strlen("1") == 1, "strlen (len=1)", "strlen (len=1)");
    test_assert(strlen("12") == 2, "strlen (len=2)", "strlen (len=2)");
    test_assert(strlen("123") == 3, "strlen (len=3)", "strlen (len=3)");
    test_assert(strlen("1234") == 4, "strlen (len=4)", "strlen (len=4)");
    test_assert(strlen("12345") == 5, "strlen (len=5)", "strlen (len=5)");
}

static inline void yutsu_builtin_tests_strcmp(void)
{
    test_assert(strcmp("abc", "abc") == 0, "strcmp equal", "strcmp equal");
    test_assert(strcmp("abc", "abd") < 0, "strcmp less than", "strcmp less than");
    test_assert(strcmp("abd", "abc") > 0, "strcmp greater than", "strcmp greater than");
    test_assert(strcmp("a", "") > 0, "strcmp vs empty", "strcmp vs empty");
    test_assert(strcmp("", "a") < 0, "empty vs strcmp", "empty vs strcmp");
    test_assert(strcmp("", "") == 0, "empty vs empty", "empty vs empty");
}

static inline void yutsu_builtin_tests_itoa(void)
{
    char buf[12];

    test_assert(strcmp(itoa(0, buf, 12), "0") == 0, "itoa(0)", "itoa(0)");
    test_assert(strcmp(itoa(123, buf, 12), "123") == 0, "itoa(123)", "itoa(123)");
    test_assert(strcmp(itoa(-456, buf, 12), "-456") == 0, "itoa(-456)", "itoa(-456)");
    test_assert(strcmp(itoa(2147483647, buf, 12), "2147483647") == 0, "itoa(INT_MAX)", "itoa(INT_MAX)");
    test_assert(strcmp(itoa(-2147483648, buf, 12), "-2147483648") == 0, "itoa(INT_MIN)", "itoa(INT_MIN)");
}

/**
 * public
 */

u8 yutsu_builtin_tests_string(void)
{
    show("\nRunning String tests...\n");
    yutsu_builtin_tests_strlen();
    yutsu_builtin_tests_strcmp();
    yutsu_builtin_tests_itoa();
    show("\nString tests finished.\n");
    return YUTSUOS_SUCCESS;
}
