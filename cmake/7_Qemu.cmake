find_program(QEMU_EXECUTABLE qemu-system-i386 REQUIRED)

add_custom_target(run
    COMMAND ${QEMU_EXECUTABLE} -s -cdrom ${ISO_FILE}
    DEPENDS iso
    COMMENT "Launching YutsuOS with QEMU from ISO"
    VERBATIM
)
