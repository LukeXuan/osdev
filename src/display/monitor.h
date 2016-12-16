#ifndef MONITOR_H
#define MONITOR_H

/**
 *  Do not use this library together with the framebuffer library, unless you
 *  know what you are doing.
 */


/** monitor_print:
 *  Print on the monitor thourgh frame buffer, and automatically sets the cursor.
 *
 *  @param text the string to be printed
 *  @param len the length of the string
 */

void monitor_print(char * text, unsigned int len);

/** monitor_set_color:
 *  Set the color of the monitor.
 *
 *  @param fg the new foreground color
 *  @param bg the new background color
 */

void monitor_set_color(unsigned short fg, unsigned short bg);

/** monitor_clean:
 *  Clean the monitor.
 */

void monitor_clean();

/** monitor_move_cursor:
 *  Move cursor to the given place.
 *
 *  @param pos the position of the buffer.
 *         pos = 80 * ROW + COL
 */

void monitor_move_cursor(unsigned short pos);

#endif
