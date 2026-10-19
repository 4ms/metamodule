cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The A35 (AArch64) application project for the MetaModule MP2 ("pro").
# The M33 coprocessor firmware is a separate arm-none-eabi project (src/core_m33),
# built as an ExternalProject and embedded in the A35 image; a single CMake project
# cannot mix the two toolchains, which is also why this is a sibling project to firmware/ rather than a
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

# Until p1 boards arrive, bring-up runs on the mp2-devboard with a test carrier
# (the stm32mp2-baremetal breakout + a PCM3168 module). Select its wiring with:
#   cmake --preset pro -DMP2_TEST_CARRIER=ON
option(MP2_TEST_CARRIER "Build for the mp2-devboard test carrier instead of the pro p1 board" OFF)
if(MP2_TEST_CARRIER)
  add_compile_definitions(MP2_TEST_CARRIER)
  message(STATUS "Building for the mp2-devboard test carrier (not pro p1)")
endif()

# Console log level for pr_err(), pr_warn(), etc. (shared with the M33 build)
set(LOG_LEVEL WARN CACHE STRING "Console log level")
include(${FWDIR}/cmake/log_levels.cmake)
enable_logging()

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

# Include paths for HAL, CMSIS, and mdrivlib, used by every target.
# (An INTERFACE target, since linking an OBJECT library into a static library would copy its objects.)
add_library(mp2_interface INTERFACE)
target_include_directories(mp2_interface INTERFACE
  src/core_a35
  ${MP2_HAL_DIR}/Inc
  ${MP2_CMSIS_CORE_DIR}/Include
  ${MP2_CMSIS_CORE_DIR}/Core_A/Include
  ${MP2_CMSIS_DEVICE_DIR}/Include
  ${MDRIVLIB}
  ${MDRIVLIB}/target/stm32mp2
  ${MDRIVLIB}/target/stm32mp2_ca35
  ${FWDIR}/lib/cpputil
)

add_library(mp2_hal OBJECT ${MP2_HAL_MODULES})
target_link_libraries(mp2_hal PUBLIC mp2_interface)
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
target_link_libraries(mp2_mdrivlib PUBLIC mp2_interface)

#
# LVGL (same library and config as MP1, with MP2 overrides in src/core_a35/lv_conf.h)

set(LV_CONF_PATH ${CMAKE_CURRENT_LIST_DIR}/src/core_a35/lv_conf.h CACHE STRING "" FORCE)
add_subdirectory(${FWDIR}/lib/lvgl ${CMAKE_CURRENT_BINARY_DIR}/lvgl)
target_link_libraries(lvgl PRIVATE mp2_interface)

#
# MetaModule GUI: SquareLine Studio export (screens, fonts, images) and its C++ helpers

add_subdirectory(${FWDIR}/src/gui/slsexport ${CMAKE_CURRENT_BINARY_DIR}/slsexport)
target_include_directories(ui_lvgl PRIVATE ${FWDIR}/lib)


#
# Cortex-M33 firmware: a separate project (arm-none-eabi toolchain), embedded in the A35 image

# Where the A35 loads the M33 image, and the M33's whole memory (code, data, heap, stack).
# DDR: inside TF-A's 512MB secure DDR window (0x80000000-0x9FFFFFFF), clear of TF-A/OP-TEE
# (0x81FC0000-0x83FFFFFF), the A35 image (0x88000000), and A35 RAM/framebuffers (0x90000000+).
# The A35 opens it to the M33 with an extra RISAF4 region before starting it.
# (The M33 also runs from SRAM2: 0x0E060000 with size 0x1F000, its secure instruction-fetch alias.)
set(M33_LOAD_ADDR 0x8C000000)
set(M33_REGION_SIZE 0x2000000)

# Memory shared by the A35 and M33: non-cacheable on both, opened to both cores in RISAF4.
# Starts with .sharedmemindex (the pointers to the shared objects, at a fixed address both
# cores link), followed by .sharedmem (the objects). 2MB-aligned: the A35 MMU maps it as one block.
set(SHAREDMEM_ADDR 0x9A000000)
set(SHAREDMEM_SIZE 0x200000)

include(ExternalProject)
ExternalProject_Add(
  core_m33
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src/core_m33
  BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/core_m33
  CMAKE_ARGS -DM33_LOAD_ADDR=${M33_LOAD_ADDR} -DM33_REGION_SIZE=${M33_REGION_SIZE}
             -DSHAREDMEM_ADDR=${SHAREDMEM_ADDR} -DSHAREDMEM_SIZE=${SHAREDMEM_SIZE}
             -DMP2_TEST_CARRIER=${MP2_TEST_CARRIER} -DLOG_LEVEL=${LOG_LEVEL}
  INSTALL_COMMAND ""
  BUILD_ALWAYS ON
  BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/core_m33/main_m33.bin
)
set(M33_BIN ${CMAKE_CURRENT_BINARY_DIR}/core_m33/main_m33.bin)

#
# A35 application

add_library(
  a35_core OBJECT
  src/core_a35/main.cc
  src/core_a35/system_init.cc
  src/core_a35/m33_firmware.S
  ${FWDIR}/src/gui/slsexport/ui_local.cc
  src/core_a35/uart_print.c
  system/mmu_ca35.cc
  system/sbrk.cc
  system/syscall_stubs.c
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/startup_ca35.s
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/vectors.S
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/irq_init.c
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/esr_decode.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/drivers/interrupt_handler.cc
  ${FWDIR}/system/libc_stub.c
)

target_link_libraries(a35_core PUBLIC mp2_interface lvgl::lvgl ui_lvgl)
add_dependencies(a35_core core_m33)
target_compile_definitions(
  a35_core PRIVATE M33_LOAD_ADDR=${M33_LOAD_ADDR} M33_REGION_SIZE=${M33_REGION_SIZE} SHAREDMEM_ADDR=${SHAREDMEM_ADDR}
                   SHAREDMEM_SIZE=${SHAREDMEM_SIZE}
)
set_source_files_properties(
  src/core_a35/m33_firmware.S PROPERTIES COMPILE_DEFINITIONS "M33_FIRMWARE_BIN=\"${M33_BIN}\"" OBJECT_DEPENDS ${M33_BIN}
)
# LVGL's headers OR together values from different enums (deprecated in C++20); MP1 silences this too
target_compile_options(a35_core PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>)

target_include_directories(
  a35_core
  PUBLIC src
         src/pro
         ${FWDIR}
         ${FWDIR}/src
         ${FWDIR}/src/console
         ${FWDIR}/lib
         ${FWDIR}/lib/patch-serial
         ${FWDIR}/metamodule-plugin-sdk/core-interface
         ${FWDIR}/metamodule-plugin-sdk/core-interface/filesystem
         ${FWDIR}/lib/fatfs/source
         ${FWDIR}/src/fs/fatfs
)

add_executable(main_a35.elf $<TARGET_OBJECTS:a35_core> $<TARGET_OBJECTS:mp2_mdrivlib> $<TARGET_OBJECTS:mp2_hal>)
target_link_libraries(main_a35.elf PRIVATE ui_lvgl lvgl::lvgl)

set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/system/stm32mp2xx_ca35.ld)
target_link_options(
  main_a35.elf PRIVATE -T${LINKER_SCRIPT} -Wl,-Map,main_a35.map,--cref -Wl,--defsym=SHAREDMEM_ADDR=${SHAREDMEM_ADDR}
  -Wl,--defsym=SHAREDMEM_SIZE=${SHAREDMEM_SIZE}
)
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
