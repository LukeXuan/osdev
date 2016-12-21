#include "../utils/io.h"
#include "serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_CONTROL_PORT(com),
         inb(SERIAL_LINE_CONTROL_PORT(com)) | SERIAL_LINE_DLAB);
    outb(SERIAL_DATA_PORT(com), divisor >> 8);
    outb(SERIAL_DATA_PORT(com) + 1, divisor & 0xFF);
    outb(SERIAL_LINE_CONTROL_PORT(com),
         inb(SERIAL_LINE_CONTROL_PORT(com)) | (0xFF ^ SERIAL_LINE_DLAB));
}

void serial_configure_line(unsigned short com, unsigned char config) {
    outb(SERIAL_LINE_CONTROL_PORT(com), config);
}

void serial_configure_fifo(unsigned short com, unsigned char config) {
    outb(SERIAL_FIFO_CONTROL_PORT(com), config);
}

void serial_setup(unsigned short com, unsigned short divisor) {
    serial_configure_baud_rate(com, divisor);
    serial_configure_line(com, SERIAL_LINE_LEN_8);
    serial_configure_fifo(com, (SERIAL_FIFO_TRIGGER_14 |
                                SERIAL_FIFO_CLEAR_TRANSMIT |
                                SERIAL_FIFO_CLEAR_RECEIVE |
                                SERIAL_FIFO_ENABLE));
    outb(SERIAL_MODEM_CONTROL_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write_block(unsigned short com, unsigned short data) {
    while (serial_is_transmit_fifo_empty(com));

    outb(SERIAL_DATA_PORT(com), data);
}

void serial_print_block(unsigned short com, const char * const str) {
    const char * ptr = str;
    while (*ptr) {
        serial_write_block(com, *ptr);
        ++ ptr;
    }
}
