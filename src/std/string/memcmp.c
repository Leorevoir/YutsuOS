#include <YutsuOS/std/string.h>

i32 memcmp(const void *ptr1, const void *ptr2, const u32 num)
{
    const u8 *p1 = (const u8 *)ptr1;
    const u8 *p2 = (const u8 *)ptr2;

    for (u32 i = 0; i < num; ++i)
    {
        if (p1[i] != p2[i])
        {
            return (i32)p1[i] - (i32)p2[i];
        }
    }
    return 0;
}
