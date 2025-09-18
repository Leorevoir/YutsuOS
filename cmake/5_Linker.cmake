function(apply_linker_settings target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        find_program(MOLD_LINKER mold)
        if(MOLD_LINKER)
            get_property(N CACHE PROCESSOR_COUNT PROPERTY VALUE)
            if(NOT N)
                include(ProcessorCount)
                ProcessorCount(N)
            endif()
            
            if(NOT N EQUAL 0)
                target_link_options(${target} PRIVATE 
                    -fuse-ld=mold 
                    -Wl,--threads=${N}
                )
                message(STATUS "INFO: using mold linker with ${N} threads for target ${target}")
            endif()
        endif()
    endif()
endfunction()
