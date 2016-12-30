#include "gdt.h"
#include "../utils/log.h"
#include "segment.h"
#include "../utils/log.h"

#define GDT_MAX 8192

/** gdt_load (implemented in gdt_s.asm)
 *  load the gdt descriptor into GDTR.
 */

extern void gdt_load_register(struct gdt_descriptor *gdtd);

extern void segment_load_ds(unsigned short offset);
extern void segment_load_es(unsigned short offset);
extern void segment_load_ss(unsigned short offset);
extern void segment_load_cs(unsigned short offset);

struct segment_descriptor _builtin_gdt[GDT_MAX];

int gdt_set_size(unsigned int address, unsigned short size) {
    if (size > GDT_MAX) {
        log_print(LOG_ERROR, "GDT size exceeds");
        return -1;
    }

    gdtd.address = address;
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

    gdt_set_descriptor(2, &kernel_data);
    gdt_set_descriptor(1, &kernel_code);

    gdt_set_size((unsigned int) &_builtin_gdt, 3);

    segment_load_ds(2 * sizeof(struct segment_descriptor));
    segment_load_es(2 * sizeof(struct segment_descriptor));
    segment_load_ss(2 * sizeof(struct segment_descriptor));
    segment_load_cs(1 * sizeof(struct segment_descriptor));

    log_print(LOG_DEBUG, "Segment register loaded");
}
