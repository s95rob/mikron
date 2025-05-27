#include "kernel/serial.h"

void kernel_main() {
    serial_init(SERIAL_DEFAULT_BAUDRATE);
    serial_puts("hello world\n");

    while(1);
}