#ifndef YUTSUOS_STD_IO_H
#define YUTSUOS_STD_IO_H

#include <YutsuOS/std/types.h>

u8 yutsuos_io_inb(const u16 port);
void yutsuos_io_outb(const u16 port, const u8 value);

#endif /* YUTSUOS_STD_IO_H */
