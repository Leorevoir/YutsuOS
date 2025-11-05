# show

## High-level:

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

You can also specify the color using `show_color()`, also defined in `std/io.h` as:

```c
/**
 * @brief show formatted output to the TTY with color
 * @param color The color to use (use VGA color codes)
 * @param fmt The format string
 * @param ... The arguments to format
 */
void show_color(const u8 color, const char *fmt, ...);
```

## Low-level:

`show()` function uses variadic list (_va_list_). As `<stdarg.h>` is from the GLibC, we cannot use it in our kernel. In order to get the _va_list_, we have to move manually the pointers:

```c
void show(const char *fmt, ...)
{
    i32 *args = (i32 *)(&fmt + 1);
    ...
}
```

As _write_ is defined in `<unistd.h>`, from the GLibC, we cannot use it in our kernel. `show()` uses `core/vga.h` and its low-level abstractions to _write_ text on the screen (the vga buffer)
