# Array

`array.h` is a header defined in `std/array.h`. It implements the `Array` type:

```c
typedef struct
{
    u32 size;
    char **data;
} Array;

/**
 * @brief Parses a string into an array of arguments.
 *
 * This function splits a string by whitespace, allocating memory for an
 * array of strings and for each individual argument string.
 *
 * @param str The input string to parse.
 * @return An Array struct containing the size and data.
 */
Array array_from_string(const char *str);

/**
 * @brief Liberates the memory allocated for an Array structure.
 *
 * This function iterates through the 'data' array, freeing each individual
 * string, and then frees the 'data' array itself. It's crucial to call this
 * after you are done with an array created by array_from_string to prevent
 * memory leaks.
 *
 * @param arr A pointer to the Array to be freed.
 */
void array_free(Array *arr);
```

This is a _safe_ array, for now used to _split_ strings by whitespace. You can construct it with:

```c
#include <YutsuOS/std/array.h>

int main(void)
{
    Array array = array_from_string("hello         this is a\ttext");

    for (u32 i = 0; i < size; ++i) {
        show(array.data[i]);
    }
    array_free(&array);
}
```

You also can _auto-cleanup_ the array memory at the end of the block by building it with the macro `defer_array_free` :

```c
#include <YutsuOS/std/array.h>

int main(void)
{
    defer_array_free Array array = array_from_string("same  test\t:D\n");

    /* ... */
}
/* array is automatically cleanup after the main here, no leaks are possible */
```
