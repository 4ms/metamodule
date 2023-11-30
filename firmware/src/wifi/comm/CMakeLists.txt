# 
# Flatbuffers
# (Manually create a target because original cmake includes the flatc compiler)
# 

add_library(flatbuffers INTERFACE)
target_include_directories(flatbuffers INTERFACE ${FWDIR}/lib/flatbuffers/include/)

# Locate flatbuffer compiler
# This falls back to the local flatabuffers repository if not found on PATH
find_program(FLATBUFFERS_FLATC_EXECUTABLE flatc
    PATHS ${FWDIR}/lib/flatbuffers/build
    REQUIRED)
message("Found flatbuffers compiler at " ${FLATBUFFERS_FLATC_EXECUTABLE})

# Compile flat buffer definitions to cpp headers
set(COMPILED_FLATBUFFER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/flat)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${FWDIR}/lib/flatbuffers/CMake)
include(BuildFlatBuffers)
build_flatbuffers(flat/all.fbs "" flatbuffer_messages_utils "" ${COMPILED_FLATBUFFER_OUTPUT_DIR} "" "")

# Create library with generated flatbuffer headers
add_library(flatbuffer_messages INTERFACE)
add_dependencies(flatbuffer_messages flatbuffer_messages_utils)
target_include_directories(flatbuffer_messages INTERFACE ${COMPILED_FLATBUFFER_OUTPUT_DIR})

# Sources

target_sources(main_m4.elf PRIVATE
    ${WIFI_DIR}/comm/wifi_interface.cc
    ${WIFI_DIR}/comm/BufferedUSART2.h
    ${WIFI_DIR}/comm/BufferedUSART2.cpp
    ${WIFI_DIR}/comm/framing/Configuration.h
    ${WIFI_DIR}/comm/framing/Deframer.hpp
    ${WIFI_DIR}/comm/framing/Deframer.h
    ${WIFI_DIR}/comm/framing/DynamicDeframer.h
    ${WIFI_DIR}/comm/framing/Framer.h
    ${WIFI_DIR}/comm/framing/StaticDeframer.h
)


## Add dependencies to firmware
target_link_libraries(main_m4.elf PUBLIC flatbuffers flatbuffer_messages)