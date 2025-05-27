.section ".text.boot"
.globl _start
.org 0x8000

// entrypoint
// r15 (pc) = 0x8000
// r0       = 0x0
// r1       = 0x0c42 (machine ID)
// r2       = 0x0100 (start ATAGS)
_start:
    // setup kernel stack, moving down from boot ROM
    mov sp, #0x8000

    // clear bss
    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b 2f

    // move away from bss segment
1:
    stmia r4!, {r5-r8}

2:
    cmp r4, r9
    blo 1b

    // call kernel_main
    ldr r3, =kernel_main
    blx r3

    // infinite loop
halt:
    wfe
    b halt
