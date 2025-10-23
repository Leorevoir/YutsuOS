#include <YutsuOS/std/memory.h>
#include <YutsuOS/std/string.h>

char *strdup(const char *str)
{
    const u32 len = strlen(str);
    char *str_copy = allocate(len + 1);

    if (!str_copy)
    {
        return NULL;
    }
    memcpy(str_copy, str, len);
    str_copy[len] = '\0';
    return str_copy;
}
