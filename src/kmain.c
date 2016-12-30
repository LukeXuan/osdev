#include "utils/monitor.h"
#include "devices/serial.h"
#include "utils/log.h"
#include "memory/gdt.h"

void kmain() {
    log_setup(LOG_BACKEND_COM1);
    monitor_clean();

    gdt_init();

    monitor_print("Hello World!");

    return;
}
