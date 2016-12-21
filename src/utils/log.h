#ifndef LOG_H
#define LOG_H

#define LOG_BACKEND_SCREEN		0x000
#define LOG_BACKEND_COM1		0x3F8
#define LOG_BACKEND_COM2		0x2F8
#define LOG_BACKEND_COM3		0x3E8
#define LOG_BACKEND_COM4		0x2E8

#define LOG_ERROR				0x00
#define LOG_WARNING				0x01
#define LOG_INFO				0x02
#define LOG_DEBUG				0x03

/** log_setup:
 *  Sets up the log facility with its backend.
 *
 *  @param backend		The backend to be used
 */

void log_setup(unsigned short backend);

/** log_print:
 *  Prints the message with corresponding log level.
 *
 *	@param level		The log level
 *	@param message		The message to be printed
 */

void log_print(unsigned char level, const char * const message);

#endif
