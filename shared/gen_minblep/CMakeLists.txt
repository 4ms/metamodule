cmake_minimum_required(VERSION 3.22)
project(MinBLEP)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/minblep_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/minblep.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../firmware/src/VCV_adaptor/pffft/pffft.c
    ${CMAKE_CURRENT_LIST_DIR}/../cpputil/util/math_tables.cc
)

set(CXX c++)
set(CMAKE_CXX_STANDARD 20)
set(DEPFLAGS -MMD -MP -MF) 

set(FW_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../firmware/)
message(STATUS "FW_ROOT: ${FW_ROOT}")

add_executable(gen_minblep ${SOURCES})

target_include_directories(gen_minblep PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../firmware/src/
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${CMAKE_CURRENT_LIST_DIR}/../cpputil
)

add_custom_command(
    OUTPUT ${FW_ROOT}/src/VCV_adaptor/dsp/minblep_16_32.h
    COMMAND gen_minblep 16 32 > ${FW_ROOT}/src/VCV_adaptor/dsp/minblep_16_32.h
    DEPENDS gen_minblep
)

add_custom_target(generate_minblep_files DEPENDS ${FW_ROOT}/src/VCV_adaptor/dsp/minblep_16_32.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)