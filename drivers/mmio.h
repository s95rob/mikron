#pragma once

#include <stdint.h>

// Set memory-mapped byte (8bits)
void mmio_outb(uint32_t port, uint8_t value);

// Set memory-mapped word (16bits)
void mmio_outw(uint32_t port, uint16_t value);

// Set memory-mapped long word (32bits)
void mmio_outl(uint32_t port, uint32_t value);

// Return memory-mapped byte (8bits)
uint8_t mmio_inb(uint32_t port);

// Return memory-mapped word (16bits)
uint16_t mmio_inw(uint32_t port);

// Return memory-mapped long word (32bits)
uint32_t mmio_inl(uint32_t port);