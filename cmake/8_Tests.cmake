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
