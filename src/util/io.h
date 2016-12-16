#ifndef IO_H
#define IO_H

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.asm
 *
 *  @param port The I/O port to send the data
 *  @param data The data to send to the I/O port (in byte)
 */

void outb(unsigned short port, unsigned char data);

#endif
