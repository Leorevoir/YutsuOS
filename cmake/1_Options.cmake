set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(KERNEL_NAME yutsuos)

########################################
# Release Optimizations
########################################

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

########################################
# Find NASM
########################################

find_program(NASM_EXECUTABLE NAMES nasm)
if(NOT NASM_EXECUTABLE)
    find_program(AS_EXECUTABLE NAMES as)
    if(NOT AS_EXECUTABLE)
        message(FATAL_ERROR "ERROR: nasm or as not found! Please install nasm or as.")
    else()
        message(STATUS "INFO: as found: ${AS_EXECUTABLE}")
        set(NASM_EXECUTABLE ${AS_EXECUTABLE})
    endif()
else()
    message(STATUS "INFO: nasm found: ${NASM_EXECUTABLE}")
endif()

########################################
# Debug Options
########################################

option(ENABLE_DEBUG "Enable YUTSUOS_DEBUG macro" OFF)
if(ENABLE_DEBUG)
    add_compile_definitions(YUTSUOS_DEBUG=1)
    message(STATUS "INFO: YUTSUOS_DEBUG enabled")
endif()

########################################
# Test Options
########################################

option(ENABLE_TESTS "Enable building tests" OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
