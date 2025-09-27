#include <YutsuOS/std/string.h>

/**
 * public
 */

void *memcpy(void *dest, const void *src, u32 n)
{
    u8 *d = (u8 *)dest;
    const u8 *s = (const u8 *)src;

    for (u32 i = 0; i < n; ++i)
    {
        d[i] = s[i];
    }
    return dest;
}
