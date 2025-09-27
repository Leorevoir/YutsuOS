#ifndef YUTSUOS_STD_ARRAY_H
#define YUTSUOS_STD_ARRAY_H

#include <YutsuOS/std/types.h>

typedef struct
{
    u32 size;
    const char **data;
} Array;

Array array_from_string(const char *str, const char delimiter);

#endif /* YUTSUOS_STD_ARRAY_H */
