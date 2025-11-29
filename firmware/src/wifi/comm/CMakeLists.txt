#
# Flatbuffers (Manually create a target because original cmake includes the flatc compiler)
#

set(FLATBUFFERS_SUBMODULE_PATH ${FWDIR}/lib/flatbuffers)

add_library(flatbuffers INTERFACE)
target_include_directories(flatbuffers INTERFACE ${FLATBUFFERS_SUBMODULE_PATH}/include/)

# Build flatbuffers compiler from submodule
include(ExternalProject)
ExternalProject_Add(
  flatc
  SOURCE_DIR ${FLATBUFFERS_SUBMODULE_PATH}/
  INSTALL_COMMAND cmake -E echo "Skipping install step for flatc"
)

# Use flatbuffers compiler executable from external project
ExternalProject_Get_Property(flatc BINARY_DIR)
set(FLATBUFFERS_FLATC_EXECUTABLE ${BINARY_DIR}/flatc)

# Compile flat buffer definitions to cpp headers
set(COMPILED_FLATBUFFER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/flat)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${FLATBUFFERS_SUBMODULE_PATH}/CMake)
include(BuildFlatBuffers)
build_flatbuffers(
  flat/all.fbs
  ""
  flatbuffer_messages_utils
  ""
  ${COMPILED_FLATBUFFER_OUTPUT_DIR}
  ""
  ""
)
add_dependencies(flatbuffer_messages_utils flatc)

# Create library with generated flatbuffer headers
add_library(flatbuffer_messages INTERFACE)
add_dependencies(flatbuffer_messages flatbuffer_messages_utils)
target_include_directories(flatbuffer_messages INTERFACE ${COMPILED_FLATBUFFER_OUTPUT_DIR})

# Sources

add_library(
  wifi_comm STATIC
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

target_include_directories(
  wifi_comm
  PRIVATE .
          ${BOARD_SUPPORT_DIR}
          ${DRIVERLIB}
          ${DRIVERLIB}/target/stm32mp1
          ${DRIVERLIB}/target/stm32mp1_cm4
          ${FWDIR}
          ${FWDIR}/lib
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          ${FWDIR}/lib/cmsis/Include
          ${FWDIR}/lib/fatfs/
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/lib/patch-serial
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/core_m4
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/system
          ${HALDIR}/include
)

# Add dependencies to firmware

target_compile_definitions(wifi_comm PRIVATE CPPUTIL_STATIC_STRING_USE_STD_STRING)

target_link_libraries(wifi_comm PUBLIC cpputil flatbuffers flatbuffer_messages)
