cmake_minimum_required(VERSION 3.16)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(ARM_NONE_EABI_MCPU_FLAG cortex-a15)
include(arm-none-eabi.toolchain)

project(mikron LANGUAGES ASM C)

add_subdirectory("libc")
add_subdirectory("kernel")
add_subdirectory("boot")