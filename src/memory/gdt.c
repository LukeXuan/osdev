#include "gdt.h"
#include "../utils/log.h"
#include "segment.h"

#define GDT_MAX 8192

/** gdt_load (implemented in gdt_s.asm)
 *  load the gdt descriptor into GDTR.
 */

extern void gdt_load_register(struct gdt_descriptor *gdtd);

extern void segment_load_registers();

struct segment_descriptor _builtin_gdt[GDT_MAX];

int gdt_set_size(unsigned short size) {
    if (size > GDT_MAX) {
        log_print(LOG_ERROR, "GDT size exceeds");
        return -1;
    }

    gdtd.limit = size * sizeof (struct segment_descriptor);

    gdt_load_register(&gdtd);

    return 0;
}

void gdt_set_descriptor(unsigned short index,
                        const struct segment_descriptor * const descriptor) {
    _builtin_gdt[index] = *descriptor;
}

void gdt_init() {
    unsigned int base = 0;
    unsigned int limit = 0xFFFFF;
    struct segment_descriptor kernel_data =
        segment_make_descriptor(limit, base,
                                SEGMENT_DATA_TYPE | SEGMENT_DATA_TYPE_WRITE,
                                1,
                                0,
                                1,
                                1,
                                1);

    struct segment_descriptor kernel_code =
        segment_make_descriptor(limit, base,
                                SEGMENT_CODE_TYPE | SEGMENT_CODE_TYPE_READ,
                                1,
                                0,
                                1,
                                1,
                                1);

    gdt_set_descriptor(1, &kernel_data);
    gdt_set_descriptor(2, &kernel_code);

    gdt_set_size(3);

    // TODO: Load segment registers
}
