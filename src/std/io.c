#include <YutsuOS/std/io.h>

/**
 * public
 */

u8 yutsuos_io_inb(const u16 port)
{
    u8 ret;

    __asm__ __volatile__("inb %[port], %[ret]" : [ret] "=a"(ret) : [port] "Nd"(port));
    return ret;
}

void yutsuos_io_outb(const u16 port, const u8 value)
{
    __asm__ __volatile__("outb %[value], %[port]" : : [value] "a"(value), [port] "Nd"(port));
}
