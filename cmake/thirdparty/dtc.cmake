# External CMakeLists for dtc submodule

set(DTC_SOURCE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/dtc")

# libfdt

set(LIBFDT_SOURCE_DIR "${DTC_SOURCE_DIR}/libfdt")

add_library(libfdt STATIC
    ${LIBFDT_SOURCE_DIR}/fdt_addresses.c
    ${LIBFDT_SOURCE_DIR}/fdt_check.c
    ${LIBFDT_SOURCE_DIR}/fdt_empty_tree.c
    ${LIBFDT_SOURCE_DIR}/fdt_overlay.c
    ${LIBFDT_SOURCE_DIR}/fdt_ro.c
    ${LIBFDT_SOURCE_DIR}/fdt_rw.c
    ${LIBFDT_SOURCE_DIR}/fdt_strerror.c
    ${LIBFDT_SOURCE_DIR}/fdt_sw.c
    ${LIBFDT_SOURCE_DIR}/fdt_wip.c
    ${LIBFDT_SOURCE_DIR}/fdt.c
)
target_include_directories(libfdt 
PUBLIC
    ${LIBFDT_SOURCE_DIR}
)

# Avoid "liblibfdt"
set_target_properties(libfdt PROPERTIES OUTPUT_NAME fdt)