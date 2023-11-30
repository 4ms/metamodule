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
    wifi_interface.cc
    BufferedUSART2.h
    BufferedUSART2.cpp
    framing/Configuration.h
    framing/Deframer.hpp
    framing/Deframer.h
    framing/DynamicDeframer.h
    framing/Framer.h
    framing/StaticDeframer.h
)

target_include_directories(main_m4.elf PRIVATE .)


## Add dependencies to firmware

target_link_libraries(main_m4.elf PUBLIC flatbuffers flatbuffer_messages lockfree)