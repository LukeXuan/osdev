#include "framebuffer.h"

struct fb_text * fb = (struct fb_text *) 0x000B8000;

void fb_write(unsigned int row, unsigned int col,  struct fb_text *text) {
    fb[row * COL_MAX + col] = *text;
}

void fb_print(unsigned int row, unsigned int col,
              char *text, unsigned char fg, unsigned char bg, unsigned int size) {
    for (unsigned int i = 0; i < size; ++ i) {
        fb[row * COL_MAX + col + i] = (struct fb_text) {text[i], fg, bg};
    }
}

void fb_clean(unsigned int fg, unsigned int bg) {
    for (unsigned int i = 0; i < ROW_MAX; ++ i) {
        for (unsigned int j = 0; j < COL_MAX; ++ j) {
            fb[i * COL_MAX + j] = (struct fb_text) {'\0', fg, bg};
        }
    }
}
