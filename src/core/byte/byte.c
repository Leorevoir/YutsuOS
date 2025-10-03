#include <YutsuOS/core/byte.h>

/**
 * public
 */

/**
 * @brief read a byte from the specified port
 * @param port the port to read from
 * @return the byte read from the port
 */
u8 __yutsuos_core_io_inb(const u16 port)
{
    u8 ret;

    __asm__ __volatile__("inb %[port], %[ret]" : [ret] "=a"(ret) : [port] "Nd"(port));
    return ret;
}

/**
 * @brief write a byte to the specified port
 * @param port the port to write to
 * @param value the value to write
 */
void __yutsuos_core_io_outb(const u16 port, const u8 value)
{
    __asm__ __volatile__("outb %[value], %[port]" : : [value] "a"(value), [port] "Nd"(port));
}

/**
 * @brief read a word from the specified port
 * @param port the port to write to (16-bit)
 * @param value the value to write (16-bit)
 */
void __yutsuos_core_io_outw(const u16 port, const u16 value)
{
    __asm__ __volatile__("outw %[value], %[port]" : : [value] "a"(value), [port] "Nd"(port));
}
