set(ISO_FILE ${CMAKE_BINARY_DIR}/yutsuos.iso)
set(ISO_DIR ${CMAKE_BINARY_DIR}/iso)

find_program(GRUB_FILE_EXECUTABLE grub-file REQUIRED)
find_program(GRUB_MKRESCUE_EXECUTABLE grub-mkrescue REQUIRED)

add_custom_command(
    OUTPUT ${ISO_FILE}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${ISO_DIR}/boot/grub
    COMMAND ${CMAKE_COMMAND} -E copy ${YUTSUOS_ELF} ${ISO_DIR}/boot/
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/grub/grub.cfg ${ISO_DIR}/boot/grub/
    COMMAND ${GRUB_FILE_EXECUTABLE} --is-x86-multiboot ${ISO_DIR}/boot/yutsuos.elf
    COMMAND ${GRUB_MKRESCUE_EXECUTABLE} -o ${ISO_FILE} ${ISO_DIR}
    DEPENDS ${YUTSUOS_ELF} ${CMAKE_SOURCE_DIR}/src/grub/grub.cfg
    COMMENT "Creating ISO image"
    VERBATIM
)

add_custom_target(iso DEPENDS ${ISO_FILE})
