########################################
# Ccache Support
########################################

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
        message(STATUS "INFO: using ccache: ${CCACHE_PROGRAM}")
    endif()
endif()

########################################
# Parallel Build
########################################

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
    set(PROCESSOR_COUNT ${N} CACHE INTERNAL "Number of processors")
    message(STATUS "INFO: setting parallel build level to ${N}")
endif()
