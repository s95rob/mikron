add_library(libc STATIC
    "memory.c"
    "string.c"
)
target_include_directories(libc 
PUBLIC
    "include"
)