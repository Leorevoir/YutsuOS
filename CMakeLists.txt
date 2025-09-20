cmake_minimum_required(VERSION 3.16)
project(yutsuos LANGUAGES C ASM_NASM VERSION 0.0.1)

########################################

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

########################################

include(1_Options)
include(2_Optimizations)
include(3_Sources)

########################################
# Build x86-32 Assembly
########################################

set(ASM_OBJECTS "")
foreach(ASM_FILE ${SRC_ASM})
    get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
    set(OBJ_FILE ${CMAKE_BINARY_DIR}/${ASM_NAME}.o)

    add_custom_command(
        OUTPUT ${OBJ_FILE}
        COMMAND ${NASM_EXECUTABLE} -f elf32 ${ASM_FILE} -o ${OBJ_FILE}
        DEPENDS ${ASM_FILE}
        COMMENT "Assembling ${ASM_FILE}"
        VERBATIM
    )

    list(APPEND ASM_OBJECTS ${OBJ_FILE})
endforeach()

########################################
# Build C Objects
########################################

set(C_OBJECTS "")
foreach(C_FILE ${SRC_YUTSUOS})
    get_filename_component(C_NAME ${C_FILE} NAME_WE)
    set(OBJ_FILE ${CMAKE_BINARY_DIR}/${C_NAME}.o)

    add_custom_command(
        OUTPUT ${OBJ_FILE}
        COMMAND ${CMAKE_C_COMPILER} -m32 -ffreestanding -fno-builtin -nostdlib -fno-stack-protector
                -Wall -Wextra -I${CMAKE_SOURCE_DIR}/include -c ${C_FILE} -o ${OBJ_FILE}
        DEPENDS ${C_FILE}
        COMMENT "Compiling ${C_FILE}"
        VERBATIM
    )

    list(APPEND C_OBJECTS ${OBJ_FILE})
endforeach()

include(5_Linker)
include(6_Iso)
include(7_Qemu)

########################################
# YutsuOS unit tests
########################################

if(ENABLE_TESTS)
    include(8_Tests)
endif()
