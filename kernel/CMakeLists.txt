add_library(kernel STATIC
    "kmain.c"
    "kmem.c"
)
target_include_directories(kernel
PUBLIC
    "kernel"
)
target_link_libraries(kernel 
PUBLIC
    libfdt
)