#include "framebuffer.h"
#include "../utils/io.h"

#define FB_COMMAND_PORT        0x3D4
#define FB_DATA_PORT           0x3D5

#define FB_HIGH_BYTE_COMMAND   14
#define FB_LOW_BYTE_COMMAND    15

struct fb_char * fb = (struct fb_char *) 0x000B8000;


void fb_write(unsigned char row, unsigned char col,  struct fb_char *data) {
    fb[row * COL_MAX + col] = *data;
}

unsigned int fb_print(unsigned char row, unsigned char col,
                      const char * const str,
                      unsigned char fg, unsigned char bg) {
    unsigned int len = 0;
    while (str[len]) {
        fb[row * COL_MAX + col + len] = (struct fb_char) {str[len], fg, bg};
        ++ len;
    }
    
    return len;
}

void fb_clean(unsigned char fg, unsigned char bg) {
    for (unsigned int i = 0; i < ROW_MAX; ++ i) {
        for (unsigned int j = 0; j < COL_MAX; ++ j) {
            fb[i * COL_MAX + j] = (struct fb_char) {'\0', fg, bg};
        }
    }
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0x00FF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos) & 0x00FF);
}
