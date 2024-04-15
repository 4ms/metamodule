cmake_minimum_required(VERSION 3.22)
project(MinBLEP)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/minblep_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/minblep.cpp
)

set(CMAKE_CXX_STANDARD 20)
set(DEPFLAGS -MMD -MP -MF) 

set(FW_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../firmware/)

add_executable(gen_minblep ${SOURCES})

target_include_directories(gen_minblep PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../firmware/src/
    ${CMAKE_CURRENT_LIST_DIR}/..
)

if (NOT cpputil::cpputil)
    add_subdirectory(../cpputil ${CMAKE_CURRENT_BINARY_DIR}/cpputil)
endif()
add_subdirectory(../../firmware/src/VCV_adaptor/pffft ${CMAKE_CURRENT_BINARY_DIR}/pffft)

target_link_libraries(gen_minblep PRIVATE cpputil pffft)

add_custom_command(
    OUTPUT ${FW_ROOT}/src/VCV_adaptor/dsp/minblep_4_32.h
    COMMAND gen_minblep 4 32 > ${FW_ROOT}/src/VCV_adaptor/dsp/minblep_4_32.h
    DEPENDS gen_minblep
)

add_custom_target(generate_minblep_files DEPENDS 
    ${FW_ROOT}/src/VCV_adaptor/dsp/minblep_4_32.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
