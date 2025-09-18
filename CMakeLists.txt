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
        COMMAND ${CMAKE_C_COMPILER} -m32 -ffreestanding -fno-builtin -nostdlib 
                -Wall -Wextra -I${CMAKE_SOURCE_DIR}/include -c ${C_FILE} -o ${OBJ_FILE}
        DEPENDS ${C_FILE}
        COMMENT "Compiling ${C_FILE}"
        VERBATIM
    )

    list(APPEND C_OBJECTS ${OBJ_FILE})
endforeach()

########################################
# Link yutsuos
########################################

set(YUTSUOS_ELF ${CMAKE_BINARY_DIR}/yutsuos.elf)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)

add_custom_command(
    OUTPUT ${YUTSUOS_ELF}
    COMMAND ${CMAKE_C_COMPILER} -m32 -ffreestanding -fno-builtin -nostdlib 
            -T ${LINKER_SCRIPT} ${ASM_OBJECTS} ${C_OBJECTS} -o ${YUTSUOS_ELF}
    DEPENDS ${ASM_OBJECTS} ${C_OBJECTS} ${LINKER_SCRIPT}
    COMMENT "Linking yutsuos"
    VERBATIM
)

add_custom_target(${KERNEL_NAME} ALL DEPENDS ${YUTSUOS_ELF})

########################################
# ISO Creation Target
########################################

include(5_Iso)

########################################
# QEMU Launch Target
########################################

include(6_Qemu)

########################################
# YutsuOS unit tests
########################################

if(ENABLE_TESTS)
    add_executable(unit_tests ${SRC_TESTS})
    set_target_properties(unit_tests PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    if(CMAKE_C_COMPILER_ID MATCHES "Clang|AppleClang")
        target_compile_options(unit_tests PRIVATE 
            -fprofile-instr-generate -fcoverage-mapping
        )
        target_link_options(unit_tests PRIVATE 
            -fprofile-instr-generate -fcoverage-mapping
        )
    elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        target_compile_options(unit_tests PRIVATE 
            -fprofile-arcs -ftest-coverage
        )
        target_link_options(unit_tests PRIVATE 
            -fprofile-arcs -ftest-coverage
        )
    endif()

    target_compile_definitions(unit_tests PRIVATE YUTSUOS_TESTS=1)
    target_link_libraries(unit_tests PRIVATE criterion)
    target_include_directories(unit_tests PRIVATE ${INCLUDE_YUTSUOS})

    include(4_Warnings)
    apply_compiler_warnings(unit_tests)

    enable_testing()
    add_test(NAME unit_tests COMMAND unit_tests)
endif()

########################################
# Test Runner Target
########################################

add_custom_target(test_run
    COMMENT "Running unit tests"
    COMMAND ${CMAKE_COMMAND} -DENABLE_TESTS=ON ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unit_tests
    COMMAND ${CMAKE_BINARY_DIR}/unit_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
