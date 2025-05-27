#pragma once

#include <stdint.h>

#define SERIAL_DEFAULT_BAUDRATE 115200

// Initialize the serial communication interface
void serial_init(uint32_t baudrate);

// Send a character over serial com
void serial_putc(char c);

// Send a zero-terminated string over serial com
void serial_puts(const char* str);

// Get a character from serial com
uint8_t serial_getc();