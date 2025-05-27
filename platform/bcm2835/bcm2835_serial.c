// BCM2835 serial driver via UART0

#include "bcm2835_peripherals.h"
#include "kernel/serial.h"
#include "kernel/mmio.h"
#include "arch/arm/armv6.h"

// Wait for specific UART IRQ
void uart_wait_irq(uint16_t irq) {
    while (mmio_inl(UART0_FR) & irq);
}

void serial_init(uint32_t baudrate) {
    // Initialize UART0

    // Bring UART0 offline while setting it up
    mmio_outl(UART0_CR, 0);

    // Disable all GPIO pins and wait
    mmio_outl(GPPUD, 0);
    arm_delay(150);

    // Disable pin 14 and 15, wait
    mmio_outl(GPPUDCLK0, BIT(14) | BIT(15));
    arm_delay(150);

    // Write changes to GPPUDCLK0 (by setting to 0)
    mmio_outl(GPPUDCLK0, 0);

    // Clear pending interrupts
    mmio_outl(UART0_ICR, 0x7ff);

    // Apply baudrate via integer and fractional baud rate registers
    // TODO: enable hardware FPU, redo in floating point
    const uint32_t fx_scalar = 1000000;

    uint32_t divisor = (UART_CLOCK_FREQ * fx_scalar) / (16 * baudrate),
        ibrd = divisor / fx_scalar,
        fbrd = ((divisor % fx_scalar) * 64 + (fx_scalar / 2)) / fx_scalar;

    mmio_outl(UART0_IBRD, ibrd);
    mmio_outl(UART0_FBRD, fbrd);

    // Enable FIFO data transmission, both channels, no parity
    mmio_outl(UART0_LCRH, 
        UART_IRQ_RX_BIT |
        UART_IRQ_TX_BIT |
        UART_IRQ_RX_TIMEOUT_BIT);

    // Mask incoming interrupts
    uint32_t irqmask = UART_IRQ_CTS_BIT | 
        UART_IRQ_RX_BIT | UART_IRQ_TX_BIT |
        UART_IRQ_RX_TIMEOUT_BIT |
        UART_IRQ_FRAME_ERR_BIT | 
        UART_IRQ_PARITY_ERR_BIT | 
        UART_IRQ_BREAK_ERR_BIT |
        UART_IRQ_OVERRUN_ERR_BIT;

	mmio_outl(UART0_IMSC, irqmask);

    // Bring UART0 back online, enable recieve and transmit lines
    mmio_outl(UART0_CR, BIT(0) | BIT(8) | BIT(9));
}

void serial_putc(char c) {
    uart_wait_irq(UART_IRQ_TX_BIT);
    mmio_outl(UART0_DR, c);
}

void serial_puts(const char* str) {
    for (uint32_t i = 0; str[i] != 0; i++)
        serial_putc(str[i]);
}

uint8_t serial_getc() {
    uart_wait_irq(UART_IRQ_RX_BIT);
    return mmio_inl(UART0_DR);
}