#ifndef YUTSUOS_CORE_BYTE_H
#define YUTSUOS_CORE_BYTE_H

#include <YutsuOS/std/types.h>

/**
 * @brief read a byte from the specified port
 * @param port the port to read from
 * @return the byte read from the port
 */
u8 __yutsuos_core_io_inb(const u16 port);

/**
 * @brief write a byte to the specified port
 * @param port the port to write to
 * @param value the value to write
 */
void __yutsuos_core_io_outb(const u16 port, const u8 value);

#endif /* YUTSUOS_CORE_BYTE_H */
