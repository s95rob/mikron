add_executable(boot 
    "startup.s"
)
target_link_options(boot
PUBLIC
    "-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)
target_link_libraries(boot 
PUBLIC 
    kernel
)

add_custom_command(TARGET boot POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary $<TARGET_FILE:boot> boot.bin
)