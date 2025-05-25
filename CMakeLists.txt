cmake_minimum_required(VERSION 3.16)

set(BUILD_PLATFORM "bcm2835")


project(mikron LANGUAGES ASM C)
include("${CMAKE_SOURCE_DIR}/platform/${BUILD_PLATFORM}.cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(PLATFORM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/platform/${BUILD_PLATFORM}")
file(GLOB_RECURSE PLATFORM_SRCS
    "${PLATFORM_SOURCE_DIR}/startup.s"
    "${PLATFORM_SOURCE_DIR}/drivers/*"
)

# Mikron
file(GLOB_RECURSE MIKRON_SRCS
    "kernel/*"
)

add_executable(${PROJECT_NAME} ${PLATFORM_SRCS} ${MIKRON_SRCS})
target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    gcc
)
target_link_options(${PROJECT_NAME}
PRIVATE
    -T "${PLATFORM_SOURCE_DIR}/linker.ld" -nostdlib
)