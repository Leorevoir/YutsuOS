########################################
# YutsuOS C Sources
########################################

file(GLOB_RECURSE SRC_YUTSUOS "src/*.c")
set(INCLUDE_YUTSUOS "${CMAKE_SOURCE_DIR}/include")

########################################
# YutsuOS Assembly Sources
########################################

file(GLOB_RECURSE SRC_ASM "src/*.asm")

########################################
# YutsuOS Unit Tests
########################################

if(ENABLE_TESTS)
    file(GLOB_RECURSE SRC_TESTS "tests/*.c")
    set(INCLUDE_TESTS "${CMAKE_SOURCE_DIR}/tests")
endif()
