#ifndef YUTSUOS_CORE_HEAP_H
#define YUTSUOS_CORE_HEAP_H

#include <YutsuOS/std/types.h>

#define YUTSUOS_CORE_HEAP_ALIGNMENT 8
#define YUTSUOS_CORE_HEAP_MAX_BINS 128

typedef struct Block Block;
typedef struct Page Page;

struct Block
{
    Block *next;
    Block *prev;
    Page *page;
    u64 size;
};

struct Page
{
    Page *next;
    Page *prev;
    u64 size;
    Block free;
};

void __yutsuos_core_heap_acquire(void);

#endif /* YUTSUOS_CORE_HEAP_H */
