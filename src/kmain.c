#include "display/framebuffer.h"

void hello() {
    fb_clean(FB_WHITE, FB_BLACK);
    fb_print(0, 0, "CYi world best", FB_WHITE, FB_BLACK, 14);
}
