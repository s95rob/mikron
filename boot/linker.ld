/* QEMU ARM virt linker */

ENTRY(_start)

MEMORY {
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 128M    /* Flash section */
    RAM (rwx)   : ORIGIN = 0x40000000, LENGTH = 2048M   /* RAM section (default 2GB) */
}

SECTIONS {
    .text : {
        KEEP(*(.text.boot))
        *(.text)
        *(.rodata)
        . = ALIGN(4);
    } > FLASH

    .data : {
        . = ALIGN(4);
        __data_start__ = .;
        *(.data)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM AT> FLASH

    /* Load symbol for LMA of .data in FLASH */
    __data_load__ = LOADADDR(.data);

    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM
}
