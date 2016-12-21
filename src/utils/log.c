#include "log.h"
#include "../devices/serial.h"
#include "../utils/monitor.h"

unsigned short current_backend;
void (*log_backend)(unsigned short, const char * const);

void log_wrapped_serial_print(unsigned short backend, const char * const str) {
    serial_print_block(backend, str);
}

void log_wrapped_monitor_print(unsigned short backend __attribute__ ((unused)),
                               const char * const str) {
    monitor_print(str);
}

void log_setup(unsigned short backend) {
    current_backend = backend;
    if (current_backend != LOG_BACKEND_SCREEN) {
        log_backend = log_wrapped_serial_print;
    }
    else {
        log_backend = log_wrapped_monitor_print;
    }
}

void log_print(unsigned char level, const char * const message) {
    switch(level) {
    case LOG_ERROR:
        log_backend(current_backend, "[\x1B[1;4;31mError\x1B[0m]    ");
        break;
    case LOG_WARNING:
        log_backend(current_backend, "[\x1B[1;4;33mWarning\x1B[0m]  ");
        break;
    case LOG_INFO:
        log_backend(current_backend, "[\x1B[4;37mInfo\x1B[0m]     ");
        break;
    case LOG_DEBUG:
        log_backend(current_backend, "[\x1B[36mDebug\x1B[0m]    ");
        break;
    }

    log_backend(current_backend, message);
    log_backend(current_backend, "\n");
}
