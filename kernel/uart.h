#pragma once

#include "kdef.h"

#include <string.h>

#define UART_BASE 0x09000000

inline static void uart_putc(char c) {
    *((vu32*)UART_BASE) = c;
}

inline static void uart_puts(const char* str) {
    u32 i = 0;
    char c = str[i];
    while (c != EOS) {
        uart_putc(c);
        c = str[++i];
    }
    uart_putc('\n');
    uart_putc('\r');
}