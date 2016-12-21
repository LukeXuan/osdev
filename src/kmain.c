#include "utils/monitor.h"
#include "devices/serial.h"
#include "utils/log.h"
#include "memory/gdt.h"

void hello() {
    log_setup(LOG_BACKEND_COM1);
    monitor_clean();

    gdt_set_size(8193);

    monitor_print("Hello World!");

    return;
}
