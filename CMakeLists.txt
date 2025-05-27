cmake_minimum_required(VERSION 3.16)

# Project options

set(BUILD_PLATFORM "bcm2835")


# CMake setup

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


project(mikron LANGUAGES ASM C)

# Platform-specific

# Includes the correct platform configuration options (including toolchain)
include(${BUILD_PLATFORM})

set(PLATFORM_SOURCE_DIR "platform/${BUILD_PLATFORM}")
file(GLOB_RECURSE PLATFORM_SRCS
    "${PLATFORM_SOURCE_DIR}/*.s"
    "${PLATFORM_SOURCE_DIR}/*.c"
)


# Mikron

file(GLOB_RECURSE MIKRON_SRCS
    "kernel/*"
)

add_executable(${PROJECT_NAME} ${PLATFORM_SRCS} ${MIKRON_SRCS})
target_include_directories(${PROJECT_NAME}
PRIVATE
    "include"
)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    gcc
)
target_link_options(${PROJECT_NAME}
PRIVATE
    -T "${CMAKE_SOURCE_DIR}/platform/${BUILD_PLATFORM}_linker.ld" -nostdlib
)
set_target_properties(${PROJECT_NAME}
PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}_${BUILD_PLATFORM}
)