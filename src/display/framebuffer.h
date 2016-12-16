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

void fb_write(unsigned int row, unsigned int col, struct fb_text *text);

void fb_print(unsigned int row, unsigned int col,
              char *text, unsigned char fg, unsigned char bg, unsigned int size);

void fb_clean(unsigned int fg, unsigned int bg);
