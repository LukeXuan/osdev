#include "framebuffer.h"
#include "../util/io.h"

#define FB_COMMAND_PORT        0x3D4
#define FB_DATA_PORT           0x3D5

#define FB_HIGH_BYTE_COMMAND   14
#define FB_LOW_BYTE_COMMAND    15

struct fb_text * fb = (struct fb_text *) 0x000B8000;


void fb_write(unsigned char row, unsigned char col,  struct fb_text *text) {
    fb[row * COL_MAX + col] = *text;
}

void fb_print(unsigned char row, unsigned char col,
              char *text, unsigned char fg, unsigned char bg, unsigned int size) {
    for (unsigned int i = 0; i < size; ++ i) {
        fb[row * COL_MAX + col + i] = (struct fb_text) {text[i], fg, bg};
    }
}

void fb_clean(unsigned char fg, unsigned char bg) {
    for (unsigned int i = 0; i < ROW_MAX; ++ i) {
        for (unsigned int j = 0; j < COL_MAX; ++ j) {
            fb[i * COL_MAX + j] = (struct fb_text) {'\0', fg, bg};
        }
    }
}

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0x00FF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos) & 0x00FF);
}
