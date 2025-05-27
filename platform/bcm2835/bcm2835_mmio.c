#include "bcm2835_peripherals.h"
#include "kernel/mmio.h"
#include "arch/arm/armv6.h"

void mmio_outb(uint32_t port, uint8_t value) {
    *(volatile uint8_t*)(MMIO_BASE + port) = value;
    arm_memory_barrier();
}

void mmio_outw(uint32_t port, uint16_t value) {
    *(volatile uint16_t*)(MMIO_BASE + port) = value;
    arm_memory_barrier();
}

void mmio_outl(uint32_t port, uint32_t value) {
    *(volatile uint32_t*)(MMIO_BASE + port) = value;
    arm_memory_barrier();
}

uint8_t mmio_inb(uint32_t port) {
    arm_sync_barrier();
    return *(volatile uint8_t*)(MMIO_BASE + port);
}

uint16_t mmio_inw(uint32_t port) {
    arm_sync_barrier();
    return *(volatile uint16_t*)(MMIO_BASE + port);
}

uint32_t mmio_inl(uint32_t port) {
    arm_sync_barrier();
    return *(volatile uint32_t*)(MMIO_BASE + port);
}