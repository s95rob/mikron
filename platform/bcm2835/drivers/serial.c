#include "drivers/serial.h"
#include "drivers/mmio.h"
#include "platform/bcm2835/bcm2835_peripherals.h"
#include "arch/arm/arm.h"

typedef enum {
    UART_LINE_RECEIVE    = (1 << 4),
    UART_LINE_TRANSMIT   = (1 << 5)
} uart_line;

// Wait until UART line is ready
void uart_wfl(uart_line line) {
    while (mmio_inl(UART0_FR) & line);
}

void serial_init(uint32_t baudrate) {
    // Initialize UART

    // Bring UART0 offline while setting it up
    mmio_outl(UART0_CR, 0);

    // Disable all GPIO pins and wait
    mmio_outl(GPPUD, 0);
    arm_delay(150);

    // Disable pin 14 and 15, wait
    mmio_outl(GPPUDCLK0, (1 << 14) | (1 << 15));
    arm_delay(150);

    // Write changes to GPPUDCLK0 (by setting to 0)
    mmio_outl(GPPUDCLK0, 0);

    // Clear pending interrupts
    mmio_outl(UART0_ICR, 0x7ff);

    // Apply baudrate via integer and fractional baud rate registers
    const uint32_t fx_scalar = 1000000;

    uint32_t divisor = (UART_CLOCK_FREQ * fx_scalar) / (16 * baudrate),
        ibrd = divisor / fx_scalar,
        fbrd = ((divisor % fx_scalar) * 64 + (fx_scalar / 2)) / fx_scalar;

    mmio_outl(UART0_IBRD, ibrd);
    mmio_outl(UART0_FBRD, fbrd);

    // Enable FIFO data transmission, no parity
    mmio_outl(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    // Mask all interrupts
	mmio_outl(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    // Bring UART0 back online, enable recieve and transmit lines
    mmio_outl(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void serial_putc(char c) {
    uart_wfl(UART_LINE_TRANSMIT);
    mmio_outl(UART0_DR, c);
}

void serial_puts(const char* str) {
    for (uint32_t i = 0; str[i] != 0; i++)
        serial_putc(str[i]);
}

uint8_t serial_getc() {
    uart_wfl(UART_LINE_RECEIVE);
    return mmio_inl(UART0_DR);
}