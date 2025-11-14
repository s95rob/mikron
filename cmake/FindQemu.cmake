find_program(QEMU_SYSTEM_ARM_EXECUTABLE qemu-system-arm)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QEMU 
    REQUIRED_VARS QEMU_SYSTEM_ARM_EXECUTABLE
)