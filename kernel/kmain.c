#include "kutil.h"
#include "kmem.h"

#include <libfdt.h>

#include <memory.h>
#include <string.h>

static const char msg[] = "Hello world";

void kmain(const void* fdt) {
    // FDT test: Find UART using FDT instead of hardcoding address
    vu32* uart_base = (vu32*)0;

    // Validate FDT header
    if (fdt_check_header(fdt) == 0) {
        // Find PL011 UART property offset
        int uart_offset = fdt_node_offset_by_compatible(fdt, -1, "arm,pl011");

        if (uart_offset > 0) {
            // Get the base address from the reg property
            int prop_len;
            const fdt64_t* reg_prop = fdt_getprop(fdt, uart_offset, "reg", &prop_len);

            if (reg_prop != NULL) {
                uart_base = (vu32*)fdt64_to_cpu(*reg_prop);

                // Transmit message over UART
                for (u32 i = 0; i < strnlen(msg, sizeof(msg)); i++) {
                    *uart_base = msg[i];
                }
            }
        }
    }
}