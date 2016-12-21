#ifndef SERIAL_H
#define SERIAL_H

/* The Serial Ports */

#define SERIAL_COM1_BASE					0x3F8
#define SERIAL_COM2_BASE	    			0x2F8
#define SERIAL_COM3_BASE					0x3E8
#define SERIAL_COM4_BASE					0x2E8

/* The I/O Ports of each serial port is calculated by the value of its base
 * port address
 */

#define SERIAL_DATA_PORT(base)				(base)
#define SERIAL_FIFO_CONTROL_PORT(base)		(base + 2)
#define SERIAL_LINE_CONTROL_PORT(base)	   	(base + 3)
#define SERIAL_MODEM_CONTROL_PORT(base)		(base + 4)
#define SERIAL_LINE_STATUS_PORT(base)		(base + 5)
#define SERIAL_MODEM_STATUS_PORT(base)		(base + 6)
#define SERIAL_SCRATCH_PORT(base)			(base + 7)

/** SERIAL_LINE_CONTROL_PORT:
 *  This port is used to control the line protocol.
 *
 *  bits:		7
 *  content:	DLAB bit
 *
 *  bits:		6
 *  content: 	break control bit
 *
 *  bits:		5 4 3
 *	content:	parity bits
 *
 *	bits:		2
 *	content:	stop bit
 *
 *	bits:		1 0
 *	content:	length bits
 */

/** SERIAL_LINE_ENABLE_DLAB:
 *  The DLAB (Divisor Latch Access Bit) tells the serial port to read the
 *  highest 8 bits at offset 1 and the lowest 8 bits at offset 0
 */

#define SERIAL_LINE_DLAB					0x80
#define SERIAL_LINE_BREAK					0x40
#define SERIAL_LINE_PARITY_NONE				0x00
#define SERIAL_LINE_PARITY_ODD				0x08
#define SERIAL_LINE_PARITY_EVEN				0x18
#define SERIAL_LINE_PARITY_MARK				0x28
#define SERIAL_LINE_PARITY_SPACE			0x38
#define SERIAL_LINE_STOP					0x38
#define SERIAL_LINE_LEN_5					0x00
#define SERIAL_LINE_LEN_6					0x01
#define SERIAL_LINE_LEN_7					0x02
#define SERIAL_LINE_LEN_8					0x03

/** SERIAL_FIFO_CONTROL_PORT
 *  This port is used to control the FIFO buffer behavior
 *  bits: 		7 6
 *  content:	trigger level
 *
 *  bits:		5
 *	content:	enable 64-bit buffer
 *
 *	bits:		4
 *	content:	reserved
 *
 *	bits:		3
 *	content:	DMA(Direct Memory Access) mode select
 *
 *	bits:		2
 *	content:	Clear transmit FIFO
 *
 *	bits:		1
 *	content:	Clear receive FIFO
 *
 *	bits:		0
 *	content:	Enable FIFOs
 */

#define SERIAL_FIFO_TRIGGER_14				0xC0
#define SERIAL_FIFO_TRIGGER_8				0x80
#define SERIAL_FIFO_TRIGGER_4				0x40
#define SERIAL_FIFO_TRIGGER_1				0x00
#define SERIAL_FIFO_64						0x20
#define SERIAL_FIFO_DMA						0x08
#define SERIAL_FIFO_CLEAR_TRANSMIT			0x04
#define SERIAL_FIFO_CLEAR_RECEIVE			0x02
#define SERIAL_FIFO_ENABLE					0x01

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial port is
 *  115200 bits/s. The argument is a divisor of that number, hence the speed
 *  would be set at (115200 / arg) bits/s.
 *
 *  @ param com		The COM port
 *  @ param divisor	The divisor
 */

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/** serial_configure_line:
 *  Sets the line of the given serial port.
 *
 *	@param com		The COM port
 *  @param config	The line configuration
 */

void serial_configure_line(unsigned short com, unsigned char config);

/** serial_configure_fifo:
 *  Sets the FIFO buffer of the given serial port.
 *
 *	@param com		The COM port
 *  @param config	The FIFO configuration
 */

void serial_configure_fifo(unsigned short com, unsigned char config);

/** serial_setup:
 *  Sets the serial ports with default setting. For line, default configuration
 *  is set to 8 bits of data, 1 bit of stop and 0 bit of parity. The break
 *  control is disabled by default. For FIFO, default configuration is set
 *  to 14 bits trigger level (56 bits in 64 bits mode), clearing both buffers
 *  and enable the FIFO.
 */

void serial_setup(unsigned short com, unsigned short divisor);

/** serial_is_transmit_fifo_empty:
 *  Judges whether the transmit register is empty
 *
 *  @param com		The COM port
 */

int serial_is_transmit_register_empty(unsigned short com);

/** serial_write_block:
 *  Blocks until the transmit register is empty and then write the byte to the
 *  register
 *
 *	@param com		The COM port
 *  @param data		The data to transmit
 */

void serial_write_block(unsigned short com, unsigned short data);

/** serial_write_block:
 *  Prints with block by the transmit register.
 *
 *  @param com		The COM port
 *	@param str		The string to transmit
 */

void serial_print_block(unsigned short com, const char * const str);

#endif
