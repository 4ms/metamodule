cmake_minimum_required(VERSION 3.22)

# Cortex-M33 (CPU2) firmware for the MetaModule MP2 ("pro").
# Built as an ExternalProject of firmware-mp2/CMakeLists.txt (it needs the arm-none-eabi
# toolchain, so it can't be a target of the A35 project). The A35 embeds main_m33.bin
# and loads it to M33_LOAD_ADDR.

set(MP2_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ${MP2_DIR}/cmake/arm-none-eabi-gcc.cmake)
endif()

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "")

project(
  MetaModuleMP2_M33
  VERSION 0.1
  DESCRIPTION "MetaModule MP2 (pro) Cortex-M33"
  LANGUAGES C CXX ASM
)

set(M33_LOAD_ADDR "" CACHE STRING "Address the A35 loads the M33 image to (set by the parent project)")
set(M33_REGION_SIZE "" CACHE STRING "Size of the M33 memory region (set by the parent project)")
if(NOT M33_LOAD_ADDR OR NOT M33_REGION_SIZE)
  message(FATAL_ERROR "M33_LOAD_ADDR and M33_REGION_SIZE must be set (build this via the firmware-mp2 project)")
endif()

add_compile_definitions(M33_LOAD_ADDR=${M33_LOAD_ADDR} M33_REGION_SIZE=${M33_REGION_SIZE})

option(MP2_TEST_CARRIER "Build for the mp2-devboard test carrier instead of the pro p1 board" OFF)
if(MP2_TEST_CARRIER)
  add_compile_definitions(MP2_TEST_CARRIER)
endif()

set(FWDIR ${MP2_DIR}/../firmware)
set(MDRIVLIB ${FWDIR}/lib/mdrivlib)

include(${MP2_DIR}/cmake/arch_mp25xm33.cmake)
set_arch_flags()

add_executable(
  main_m33.elf
  main.cc
  ${MDRIVLIB}/target/stm32mp2_cm33/boot/startup_cm33.s
  ${MDRIVLIB}/target/stm32mp2_cm33/drivers/interrupt_handler.cc
  ${MDRIVLIB}/target/stm32mp2_cm33/drivers/hal_tick_stgen.cc
  ${FWDIR}/system/libc_stub.c
)

target_include_directories(
  main_m33.elf
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${MP2_DIR}/src
          ${MP2_DIR}/src/pro
          ${FWDIR}/src
          ${MDRIVLIB}
          ${MDRIVLIB}/target/stm32mp2
          ${MDRIVLIB}/target/stm32mp2_cm33
          ${FWDIR}/lib/cpputil
          ${MP2_DIR}/lib/stm32-hal/stm32mp2/Inc
          ${FWDIR}/lib/cmsis/Include
          ${MP2_DIR}/lib/cmsis-device/stm32mp257d/Include
)

set(LINKER_SCRIPT ${MP2_DIR}/system/stm32mp2xx_cm33.ld)
target_link_options(
  main_m33.elf PRIVATE
  -T${LINKER_SCRIPT}
  -Wl,--defsym=M33_LOAD_ADDR=${M33_LOAD_ADDR}
  -Wl,--defsym=M33_REGION_SIZE=${M33_REGION_SIZE}
  -Wl,-Map,main_m33.map,--cref
  --specs=nano.specs
  --specs=nosys.specs
)
set_target_properties(main_m33.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(
  TARGET main_m33.elf
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:main_m33.elf> main_m33.bin
  COMMAND ${CMAKE_SIZE_UTIL} $<TARGET_FILE:main_m33.elf>
  BYPRODUCTS main_m33.bin
  COMMENT "Creating main_m33.bin"
)
