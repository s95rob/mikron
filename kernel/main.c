#include "drivers/serial.h"

void kernel_main() {
    serial_init(SERIAL_DEFAULT_BAUDRATE);

    uint8_t* p = 0x8000000;
    *p = 'X';

    serial_putc(*p);

    while(1);
}