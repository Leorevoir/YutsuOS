#ifndef YUTSUOS_STD_MEMORY_H
#define YUTSUOS_STD_MEMORY_H

#include <YutsuOS/std/types.h>

void *allocate(const u32 size);
void liberate(void *ptr);

#endif /* YUTSUOS_STD_MEMORY_H */
