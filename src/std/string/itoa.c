#include <YutsuOS/std/string.h>

/**
 * @brief convert an integer to a char *
 * @details the buffer must be at least 12 bytes long to hold the largest possible integer
 * @param num the integer to convert
 * @param buf the buffer to write the string to
 * @param bufsize the size of the buffer
 * @return a pointer to the start of the string within the buffer
 */
char *itoa(const i32 num, char *buf, const u32 bufsize)
{
    /**
     * @info integers are at most 10 digits long, plus a sign and null terminator
     */
    if (bufsize < 12)
    {
        return buf;
    }

    char *p = buf + bufsize - 1;
    *p = '\0';

    if (num == 0)
    {
        *--p = '0';
        return p;
    }

    const bool neg = num < 0;
    u32 n = (u32)num;

    /**
     * @note: negating INT_MIN is undefined behavior, so we handle it with unsigned arithmetic
     */
    if (neg)
    {
        n = -n;
    }

    /**
     * @note: we build the string in reverse order using pointer arithmetic
     */
    do
    {
        *--p = '0' + (n % 10);
        n /= 10;
    } while (n > 0);

    if (neg)
    {
        *--p = '-';
    }

    return p;
}
