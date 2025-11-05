# IO

## Description

`io.h` is a header defined in `std/io.h`. It implements:

- show()
- show_color()
- input()
- error()

## Standards

### show()

`show()` is defined in `std/io.h` as:

```c
/**
 * @brief show formatted output to the TTY
* @param fmt The format string
 * @param ... The arguments to format
 */
void show(const char *fmt, ...);
```

It works like the GLibC `printf()` function.

```c
const char *string = "heeyy";

show("%s\t%d\n", "hello", 42);
show(string);
```

`show()` function uses variadic list (_va_list_). As `<stdarg.h>` is from the GLibC, we cannot use it in our kernel. In order to get the _va_list_, we have to move manually the pointers:

```c
void show(const char *fmt, ...)
{
    i32 *args = (i32 *)(&fmt + 1);
    ...
}
```

As _write_ is defined in `<unistd.h>`, from the GLibC, we cannot use it in our kernel. `show()` uses `core/vga.h` and its low-level abstractions to _write_ text on the screen (the vga buffer)

### show_color()

You can also specify the color using `show_color()`, defined as:

```c
/**
 * @brief show formatted output to the TTY with color
 * @param color The color to use (use VGA color codes)
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show_color(const u8 color, const char *fmt, ...);
```

### input()

`input()` is defined as:

```c
/**
 * @brief get input from the TTY
 * @param buffer The buffer to store the input
 * @param size The size of the buffer
 */
void input(char *buffer, const u32 size);
```

it works like `getline()` from the GLibC. It doesn't allocate memory, so you don't have to call `liberate()` after use.

### error()

`error()` is defined as:

```c
/**
 * @brief show formatted error message to the TTY in red color
 * @param fmt the format string
 * @param ... the arguments to format
 */
void error(const char *fmt, ...);
```

it is a complementary function with the `raise_error()` macro

```c
#define raise_error(...)                                                                                               \
    error(__VA_ARGS__);                                                                                                \
    show("\nby: %s:%d\n", __FILE__, __LINE__)
```

the error function doesn't throw a `panic()`. the goal is to _log_ your error with a beautiful format.
