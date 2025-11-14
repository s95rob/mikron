#include "uart.h"
#include "fdt.h"
#include "kmem.h"

#include <memory.h>
#include <string.h>

void kmain(const fdt_header* fdt) {
    uart_puts("Entering kmain...");

    // kmem test
    kmem_init(0x44000000);

    const char* msg = "Hello world";
    const size_t msg_len = strlen(msg);

    memblock block = kmem_block(1);

    char* str = kmem_alloc(&block, msg_len);
    memcpy(str, msg, msg_len);

    uart_puts(str);
}