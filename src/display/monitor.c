#include "monitor.h"
#include "framebuffer.h"

unsigned short monitor_row;

unsigned short monitor_col;

unsigned short monitor_fg = FB_WHITE;

unsigned short monitor_bg = FB_BLACK;

void monitor_print(char * text, unsigned int len) {
    fb_print(monitor_row, monitor_col, text, monitor_fg, monitor_bg, len);

    monitor_col += (len % COL_MAX);
    monitor_row += (len / COL_MAX);

    if (monitor_col >= COL_MAX) {
        monitor_row += 1;
        monitor_col -= COL_MAX;
    }

    fb_move_cursor(monitor_row * COL_MAX + monitor_col);
}

void monitor_set_color(unsigned short fg, unsigned short bg) {
    monitor_fg = fg;
    monitor_bg = bg;
}

void monitor_clean() {
    fb_clean(monitor_fg, monitor_bg);
}

void monitor_move_cursor(unsigned short pos) {
    monitor_row = pos / COL_MAX;
    monitor_col = pos % COL_MAX;

    fb_move_cursor(pos);
}
