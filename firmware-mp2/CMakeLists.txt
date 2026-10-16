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
# ST HAL (only the modules enabled in src/core_a35/stm32mp2xx_hal_conf.h)

set(MP2_HAL_MODULES
  hal
  hal_dma
  hal_dma_ex
  hal_dsi
  hal_i2c
  hal_i2c_ex
  hal_ltdc
  hal_rcc
  hal_rcc_ex
  hal_sai
  hal_sai_ex
)
list(TRANSFORM MP2_HAL_MODULES PREPEND ${MP2_HAL_DIR}/Src/stm32mp2xx_)
list(TRANSFORM MP2_HAL_MODULES APPEND .c)

add_library(mp2_hal OBJECT ${MP2_HAL_MODULES})
target_include_directories(mp2_hal PUBLIC
  src/core_a35
  ${MP2_HAL_DIR}/Inc
  ${MP2_CMSIS_CORE_DIR}/Include
  ${MP2_CMSIS_CORE_DIR}/Core_A/Include
  ${MP2_CMSIS_DEVICE_DIR}/Include
)
# ST's HAL casts pointers to uint32_t throughout (32-bit assumption); the
# peripheral addresses all fit in 32 bits so the truncation is harmless.
target_compile_options(mp2_hal PRIVATE -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-unused-variable)

#
# mdrivlib drivers

add_library(mp2_mdrivlib OBJECT
  ${MDRIVLIB}/drivers/pin.cc
  ${MDRIVLIB}/drivers/i2c.cc
  ${MDRIVLIB}/drivers/codec_PCM3168.cc
  ${MDRIVLIB}/target/stm32mp2/drivers/sai_tdm.cc
  ${MDRIVLIB}/target/stm32mp2/drivers/dsi_screen.cc
  ${MDRIVLIB}/target/stm32mp2/drivers/risab.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/drivers/hal_cnt.cc
)
target_link_libraries(mp2_mdrivlib PUBLIC mp2_hal)
target_include_directories(mp2_mdrivlib PUBLIC
  ${MDRIVLIB}
  ${MDRIVLIB}/target/stm32mp2
  ${MDRIVLIB}/target/stm32mp2_ca35
  ${FWDIR}/lib/cpputil
)

#
# A35 application

add_library(
  a35_core OBJECT
  src/core_a35/main.cc
  src/core_a35/system_init.cc
  src/core_a35/uart_print.c
  system/mmu_ca35.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/startup_ca35.s
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/vectors.S
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/irq_init.c
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/esr_decode.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/drivers/interrupt_handler.cc
  ${FWDIR}/system/libc_stub.c
)

target_link_libraries(a35_core PUBLIC mp2_mdrivlib)

target_include_directories(
  a35_core
  PUBLIC src
         src/pro
         ${FWDIR}/lib
)

add_executable(main_a35.elf $<TARGET_OBJECTS:a35_core> $<TARGET_OBJECTS:mp2_mdrivlib> $<TARGET_OBJECTS:mp2_hal>)

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
