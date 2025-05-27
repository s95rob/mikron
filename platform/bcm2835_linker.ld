ENTRY(_start)
PAGE_SIZE = 4096;

SECTIONS {
    /* PROG START ADDR */
    . = 0x8000;

    __start = .;

    __text_start = .;
    .text : {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(PAGE_SIZE);
    __text_end = .;

    __rodata_start = .;
    .rodata : {
        *(.rodata)
    }
    . = ALIGN(PAGE_SIZE);
    __rodata_end = .;

    __data_start = .;
    .data : {
        *(.data)
    }
    . = ALIGN(PAGE_SIZE);
    __data_end = .;

    __bss_start = .;
    .bss : {
        bss = .;
        *(.bss)
    }
    . = ALIGN(PAGE_SIZE);
    __bss_end = .;
    __bss_size = __bss_end - __bss_start;

    /* HEAP SECTION */
    __heap_start = .;
    __heap_end = 0x8000000;

    __end = .;
}