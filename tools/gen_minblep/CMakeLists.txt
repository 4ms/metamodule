cmake_minimum_required(VERSION 3.22)
project(MinBLEP)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/minblep_main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/minblep.cpp
)

set(CMAKE_CXX_STANDARD 23)
set(DEPFLAGS -MMD -MP -MF) 

set(FW_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../firmware/)
set(RACK_IF_DIR ${FW_ROOT}/metamodule-plugin-sdk/metamodule-rack-interface/include)
set(RACK_DEP_DIR ${FW_ROOT}/metamodule-plugin-sdk/metamodule-rack-interface/dep/include)

add_executable(gen_minblep ${SOURCES})

target_include_directories(gen_minblep PRIVATE
    ${FW_ROOT}/src
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${RACK_IF_DIR}
    ${RACK_DEP_DIR}
)

if (NOT cpputil::cpputil)
    add_subdirectory(../cpputil ${CMAKE_CURRENT_BINARY_DIR}/cpputil)
endif()

add_subdirectory(../../firmware/vcv_plugin/export/pffft ${CMAKE_CURRENT_BINARY_DIR}/pffft)

target_link_libraries(gen_minblep PRIVATE cpputil pffft)

add_custom_command(
    OUTPUT ${RACK_IF_DIR}/dsp/minblep_4_32.h
    COMMAND gen_minblep 4 32 > ${RACK_IF_DIR}/dsp/minblep_4_32.h
    DEPENDS gen_minblep
)

add_custom_command(
    OUTPUT ${RACK_IF_DIR}/dsp/minblep_16_16.h
    COMMAND gen_minblep 16 16 > ${RACK_IF_DIR}/dsp/minblep_16_16.h
    DEPENDS gen_minblep
)

add_custom_target(generate_minblep_files 
	DEPENDS 
		${RACK_IF_DIR}/dsp/minblep_4_32.h
		${RACK_IF_DIR}/dsp/minblep_16_16.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)
