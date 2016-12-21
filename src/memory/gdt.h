#ifndef GDT_H
#define GDT_H

#include "segment.h"

struct gdt_descriptor {
    unsigned int address;
    unsigned short limit;
} __attribute__((packed));

struct gdt_descriptor gdtd;

/** gdt_set_size:
 *  Sets the size of the GDT.
 *
 *  @param size		the size of the table
 */

int gdt_set_size(unsigned short size);

/** gdt_set_descriptor:
 *  Sets the given descriptor.
 *
 *  @param index		the index of the descriptor(offset / 8)
 *  @param descriptor	the descriptor
 */

void gdt_set_descriptor(unsigned short index,
                        const struct segment_descriptor *const descriptor);

/** gdt_init:
 *  Initiates the GDT with two kernel descriptor
 */

void gdt_init();

#endif
