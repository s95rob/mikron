add_library(kernel STATIC
    "kmain.c"
    "kmem.c"
    "fdt.c"
)
target_link_libraries(kernel
PUBLIC
    libc
)