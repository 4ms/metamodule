cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The A35 (AArch64) application project for the MetaModule MP2 ("pro").
# The M33 coprocessor firmware is a separate arm-none-eabi project added later
# (see src/core_m33/README.md); a single CMake project cannot mix the two
# toolchains, which is why this is a sibling project to firmware/ rather than a
# target inside it. Portable app code is consumed from ../firmware/src the same
# way the simulator does (include paths + firmware/src/shared_sources.cmake).

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/aarch64-none-elf-gcc.cmake)
endif()

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "")

project(
  MetaModuleMP2
  VERSION 0.1
  DESCRIPTION "MetaModule MP2 (pro)"
  LANGUAGES C CXX ASM
)

set(FWDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware)
set(MDRIVLIB ${FWDIR}/lib/mdrivlib)

include(cmake/arch_mp25xa35.cmake)
set_arch_flags()

set(MP2_CMSIS_DEVICE_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/cmsis-device/stm32mp257d)
set(MP2_CMSIS_CORE_DIR ${FWDIR}/lib/cmsis)
set(MP2_HAL_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/stm32-hal/stm32mp2)

#
# A35 application

add_library(
  a35_core OBJECT
  src/core_a35/main.cc
  src/core_a35/uart_print.c
  system/mmu_ca35.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/startup_ca35.s
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/vectors.S
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/irq_init.c
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/esr_decode.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/drivers/interrupt_handler.cc
  ${FWDIR}/system/libc_stub.c
)

target_include_directories(
  a35_core
  PUBLIC src
         src/pro
         ${MDRIVLIB}
         ${MDRIVLIB}/target/stm32mp2
         ${MDRIVLIB}/target/stm32mp2_ca35
         ${FWDIR}/lib/cpputil
         ${MP2_HAL_DIR}/Include
         ${MP2_CMSIS_CORE_DIR}/Include
         ${MP2_CMSIS_CORE_DIR}/Core_A/Include
         ${MP2_CMSIS_DEVICE_DIR}/Include
)

add_executable(main_a35.elf $<TARGET_OBJECTS:a35_core>)

set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/system/stm32mp2xx_ca35.ld)
target_link_options(main_a35.elf PRIVATE -T${LINKER_SCRIPT} -Wl,-Map,main_a35.map,--cref)
set_target_properties(main_a35.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(
  TARGET main_a35.elf
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:main_a35.elf> main_a35.bin
  COMMAND ${CMAKE_SIZE_UTIL} $<TARGET_FILE:main_a35.elf>
  COMMENT "Creating main_a35.bin"
)

# TODO (in bring-up order, see docs/MP2-Port-Plan.md):
# - image packaging: FIP for TF-A BL2 (successor of firmware/flashing/elf_to_uimg.py)
# - port firmware/src/medium/conf headers into src/pro/conf as each subsystem
#   comes up; then start compiling firmware/src/shared_sources.cmake lists here
# - src/core_m33: ExternalProject with cmake/arch_mp25xm33.cmake + arm-none-eabi
