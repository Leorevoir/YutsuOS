file(GLOB_RECURSE SRC_YUTSUOS "src/*.c")
set(INCLUDE_YUTSUOS
    "${CMAKE_SOURCE_DIR}/include"
)

if(ENABLE_TESTS)
    file(GLOB_RECURSE SRC_TESTS "tests/*.c")
    set(INCLUDE_TESTS
        "${CMAKE_SOURCE_DIR}/tests"
    )
endif()
