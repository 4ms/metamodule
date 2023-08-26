cmake_minimum_required(VERSION 3.14)

set(USE_CCACHE AUTO CACHE STRING "Use ccache to speed up builds")
set_property(CACHE USE_CCACHE PROPERTY STRINGS "AUTO;ON;OFF")


if(NOT USE_CCACHE STREQUAL "OFF")
    find_program(CCACHE_PATH ccache)
    if(CCACHE_PATH)
        message(STATUS "Enabling ccache")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PATH}")
    else()
        if (USE_CCACHE STREQUAL "ON")
            message(FATAL_ERROR "Cannot find ccache but required by USE_CCACHE")
        endif()
    endif()
endif()

