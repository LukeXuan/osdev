#ifndef FB_H
#define FB_H

#define ROW_MAX 25
#define COL_MAX 80

/* struct for framebuffer text format */

struct fb_text {
    char c;
    unsigned char fg : 4;
    unsigned char bg : 4;
} __attribute__((packed));

/* definition for colors */

#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHTGREY 7
#define FB_DARKGREY 8
#define FB_LIGHTBLUE 9
#define FB_LIGHTGREEN 10
#define FB_LIGHTCYAN 11
#define FB_LIGHTRED 12
#define FB_LIGHTMAGENTA 13
#define FB_LIGHTBROWN 14
#define FB_WHITE 15

/** fb_write:
 *  Write the given char on framebuffer at the the given location
 *
 *  @param row the row number of the location
 *  @param col the column number of the location
 *  @param text the char wrapped with fb_text
 */

void fb_write(unsigned char row, unsigned char col, struct fb_text *text);

/** fb_print:
 * Print a string on the framebuffer at the given location
 *
 *  @param row the row number of the start location
 *  @param col the column number of the start location
 *  @param text the string to be printed
 *  @param fg the foreground color of the string
 *  @param bg the background color of the string
 *  @param size the length of the string
 */

void fb_print(unsigned char row, unsigned char col,
              char *text, unsigned char fg, unsigned char bg, unsigned int size);

/** fb_clean:
 *  Clean all char in the framebuffer and reset the colors.
 * 
 *  @param fg the new foreground color
 *  @param bg the new background color
 */

void fb_clean(unsigned char fg, unsigned char bg);


/** fb_move_cursor:
 *  Move cursor to the given place.
 *
 *  @param pos the position of the buffer.
 *         pos = 80 * ROW + COL
 */

void fb_move_cursor(unsigned short pos);

#endif
