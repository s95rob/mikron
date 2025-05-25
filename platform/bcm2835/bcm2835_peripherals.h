// https://datasheets.raspberrypi.com/bcm2835/bcm2835-peripherals.pdf (pg. 5)

#pragma once

// Memory-mapped IO region base address
#define MMIO_BASE       0x20000000

// GPIO base address
#define GPIO_BASE       0x00200000

// GPIO ALL pull up/down controller
#define GPPUD           (GPIO_BASE + 0x94)

// GPIO SINGLE pull up/down controller
#define GPPUDCLK0       (GPIO_BASE + 0x98)

// UART0 base address
#define UART0_BASE      (GPIO_BASE + 0x1000)

// UART0 register addresses
#define UART0_DR        (UART0_BASE + 0x00)
#define UART0_RSRECR    (UART0_BASE + 0x04)
#define UART0_FR        (UART0_BASE + 0x18)
#define UART0_ILPR      (UART0_BASE + 0x20)
#define UART0_IBRD      (UART0_BASE + 0x24)
#define UART0_FBRD      (UART0_BASE + 0x28)
#define UART0_LCRH      (UART0_BASE + 0x2C)
#define UART0_CR        (UART0_BASE + 0x30)
#define UART0_IFLS      (UART0_BASE + 0x34)
#define UART0_IMSC      (UART0_BASE + 0x38)
#define UART0_RIS       (UART0_BASE + 0x3C)
#define UART0_MIS       (UART0_BASE + 0x40)
#define UART0_ICR       (UART0_BASE + 0x44)
#define UART0_DMACR     (UART0_BASE + 0x48)
#define UART0_ITCR      (UART0_BASE + 0x80)
#define UART0_ITIP      (UART0_BASE + 0x84)
#define UART0_ITOP      (UART0_BASE + 0x88)
#define UART0_TDR       (UART0_BASE + 0x8C)

#define UART_CLOCK_FREQ 3000000

// Mailbox register addresses
#define MBOX_BASE       0xB880
#define MBOX_READ       (MBOX_BASE + 0x00)
#define MBOX_STATUS     (MBOX_BASE + 0x18)
#define MBOX_WRITE      (MBOX_BASE + 0x20)