function(apply_compiler_warnings target)
    target_compile_options(${target} PRIVATE
        -Wall -Wextra -Werror -pedantic
        -Wconversion -Wsign-conversion
        -Wshadow -Wnull-dereference
        -Wundef -Wuninitialized
        -Winit-self -Wredundant-decls
        -Wcast-align -Wcast-qual
        -Wmissing-declarations -Wswitch-default
        -Wdouble-promotion -Wformat=2 -Wwrite-strings
    )
    message(STATUS "INFO: applied compiler warnings to target ${target}")
endfunction()
