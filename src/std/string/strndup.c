#include <YutsuOS/std/memory.h>
#include <YutsuOS/std/string.h>

char *strndup(const char *start, u32 len)
{
    char *str_copy = allocate(len + 1);

    if (!str_copy)
    {
        return NULL;
    }
    memcpy(str_copy, start, len);
    str_copy[len] = '\0';
    return str_copy;
}
