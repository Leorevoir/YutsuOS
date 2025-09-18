cmake_minimum_required(VERSION 3.16)
project(yutsuos LANGUAGES C VERSION 0.0.1)

########################################

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

########################################

include(1_Options)
include(2_Optimizations)
include(3_Sources)

########################################
# Build x86-64 Assembly
########################################


########################################
# Build C
########################################

add_executable(yutsuos ${SRC_YUTSUOS})
target_include_directories(yutsuos PRIVATE 
    INCLUDE_YUTSUOS
)

########################################

include(4_Warnings)
apply_compiler_warnings(yutsuos)

########################################

include(5_Linker)
apply_linker_settings(yutsuos)

########################################
# YutsuOS unit tests
########################################

if(ENABLE_TESTS)
    add_executable(unit_tests ${SRC_TESTS})
    set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
        target_compile_options(unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_options(unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
    endif()

    target_compile_definitions(unit_tests PRIVATE YUTSUOS_TESTS=1)
    target_link_libraries(unit_tests PRIVATE criterion)

    enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)

    target_include_directories(unit_tests PRIVATE 
        INCLUDE_YUTSUOS
    )
endif()

add_custom_target(tests_run
    COMMENT "Running unit tests"
    COMMAND ${CMAKE_COMMAND} -DBUILD_TESTS=ON ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unit_tests
    COMMAND ${CMAKE_BINARY_DIR}/unit_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
