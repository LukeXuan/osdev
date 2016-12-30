#ifndef SEGMENT_H
#define SEGMENT_H

struct segment_descriptor {
    unsigned short limit_0_16;
    unsigned int base_0_24 : 24;
    unsigned char type : 4;
    unsigned char system : 1;
    unsigned char dpl : 2;     
    unsigned char present : 1;
    unsigned char limit_16_20: 4;
    unsigned char reserved : 2;
    unsigned char db : 1;
    unsigned char granularity : 1;
    unsigned char base_24_32;
} __attribute__((packed));

#define SEGMENT_DATA_TYPE                   0x00
#define SEGMENT_DATA_TYPE_ACCESSED          0x01
#define SEGMENT_DATA_TYPE_WRITE             0x02
#define SEGMENT_DATA_TYPE_EXP_DOWN          0x04
#define SEGMENT_DATA_TYPE_EXP_DOWN          0x04
#define SEGMENT_CODE_TYPE                   0x08
#define SEGMENT_CODE_TYPE_ACCESSED          0x01
#define SEGMENT_CODE_TYPE_READ              0x02
#define SEGMENT_CODE_TYPE_CONFORM           0x04

#define segment_make_descriptor(limit, base, type, s, dpl, p, db, g) \
    (struct segment_descriptor) {                                    \
        (limit) & 0xFFFF,                                            \
        (base) & 0xFFFFFF,                                           \
        (type),                                                      \
        (s),                                                         \
        (dpl),                                                       \
        (p),                                                         \
        (limit >> 16) & 0xFF,                                        \
        0,                                                           \
        (db),                                                        \
        (g),                                                         \
        (base >> 24) & 0xFF                                          \
    }

#endif
