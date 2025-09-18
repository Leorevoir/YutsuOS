set(YUTSUOS_ELF ${CMAKE_BINARY_DIR}/yutsuos.elf)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/cmake/linker.ld)

add_custom_command(
    OUTPUT ${YUTSUOS_ELF}
    COMMAND ${CMAKE_C_COMPILER} -m32 -ffreestanding -fno-builtin -nostdlib 
            -T ${LINKER_SCRIPT} ${ASM_OBJECTS} ${C_OBJECTS} -o ${YUTSUOS_ELF}
    DEPENDS ${ASM_OBJECTS} ${C_OBJECTS} ${LINKER_SCRIPT}
    COMMENT "Linking yutsuos"
    VERBATIM
)

add_custom_target(${KERNEL_NAME} ALL DEPENDS ${YUTSUOS_ELF})
