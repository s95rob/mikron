.section .text.boot
.global _start

.extern __data_load__   @ Flash/ROM address
.extern __data_start__  @ RAM .data start address
.extern __data_end__    @ RAM .data end address
.extern __bss_start__   @ RAM .bss start address
.extern __bss_end__     @ RAM .bss end address

.extern kmain

.equ FDT_MAGIC, 0xd00dfeed     @ FDT magic number
.equ FDT_SRC, 0x40000000       @ Source location of the FDT
.equ FDT_DST, 0x44000000       @ Destination for the FDT copy

.equ STACK_TOP, 0x48000000     @ Stack pointer base

_start:
    @ Read the size of the FDT
.L_fdt_read:
    ldr r0, =FDT_SRC    @ Read FDT magic number (first 4 bytes) and increment r0 by 4
    ldr r1, [r0]
    rev r2, r1          @ Stored FDT magic number is big-endian

    @ Jump to error label if magic number does not match
    ldr r1, =FDT_MAGIC
    cmp r2, r1
    bne .L_error

    add r0, r0, #4  @ Increment r0 by 4
    ldr r1, [r0]    @ Load FDT size into r1
    rev r4, r1      @ Stored FDT size is also big-endian

    @ Move the FDT away from where the data section will go
.L_fdt_copy:
    ldr r0, =FDT_SRC        @ Source
    ldr r1, =FDT_DST        @ Destination
    mov r2, #0              @ Increment counter

.L_fdt_copy_loop:
    cmp r2, r4
    bge .L_data_copy

    ldr r3, [r0], #4    @ Load 4 bytes from FDT source, increment r0 by 4
    str r3, [r1], #4    @ Store 4 bytes to FDT destination, increment r1 by 4
    add r2, r2, #4      @ Increment the counter by 4
    b .L_fdt_copy_loop

    @ Copy .data section from ROM to RAM
.L_data_copy:
    ldr r0, =__data_load__  @ Source 
    ldr r1, =__data_start__ @ Destination
    ldr r2, =__data_end__   @ Destination end

.L_data_copy_loop:
    cmp r1, r2
    bge .L_clear_bss

    ldr r3, [r0], #4    @ Load 4 bytes from .data source, increment r0 by 4
    str r3, [r1], #4    @ Store 4 bytes to .data destination, increment r1 by 4
    b .L_data_copy_loop

    @ Clear .bss section in RAM
.L_clear_bss:
    ldr r0, =__bss_start__  @ Destination
    ldr r1, =__bss_end__    @ Destination end
    mov r2, #0              @ Value to set

.L_clear_bss_loop:
    cmp r0, r1
    bge .L_jump_kmain

    str r2, [r0], #4    @ Store 0 at r2 in .bss RAM, increment r0 by 4
    b .L_clear_bss_loop

    @ Setup stack and jump to kmain
.L_jump_kmain:
    @ Clear registers, setup stack
    mov r0, #0
    ldmia r0!, {r1-r12}
    ldr sp, =STACK_TOP

    @ Load new FDT address into r0 and call kmain
    ldr r0, =FDT_DST
    bl kmain

.L_halt:
    b .L_halt

    @ Load significant error code into all general purpose registers, freeze
.L_error:
    ldr r0, =0xAAAAAAAA     @ Scream here. 
    ldmia r0!, {r1-r12}     @ And here. 
    b .L_halt
