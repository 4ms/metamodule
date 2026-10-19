# MetaModule MP2 ("pro"): STM32MP25x, Cortex-A35 (AArch64) + Cortex-M33.
# Included by the top-level CMakeLists.txt when METAMODULE_PLATFORM is mp2 (cmake --preset mp2).
#
# The A35 application is built here. The M33 firmware (src/core_m33) needs the arm-none-eabi
# toolchain, so it's a separate CMake project, built as an ExternalProject and embedded in the
# A35 image.
# Portable app code is used from src/ the same way the simulator does (include paths, and
# src/shared_sources.cmake once the GUI comes in).

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/aarch64-none-elf-gcc.cmake)
endif()

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "")

project(
  MetaModuleMP2
  VERSION 0.1
  DESCRIPTION "MetaModule MP2 (pro)"
  LANGUAGES C CXX ASM
)

set(FWDIR ${PROJECT_SOURCE_DIR}) # used by shared CMakeLists (e.g. src/gui/slsexport), as in MP1 and the simulator
set(MDRIVLIB ${FWDIR}/lib/mdrivlib)

include(cmake/arch_mp25xa35.cmake)
set_arch_flags()

# Until p1 boards arrive, bring-up runs on the mp2-devboard with a test carrier
# (the stm32mp2-baremetal breakout + a PCM3168 module). Select its wiring with:
#   cmake --preset mp2-test-carrier
option(MP2_TEST_CARRIER "Build for the mp2-devboard test carrier instead of the pro p1 board" OFF)
if(MP2_TEST_CARRIER)
  add_compile_definitions(MP2_TEST_CARRIER)
  message(STATUS "Building for the mp2-devboard test carrier (not pro p1)")
endif()

# Console log level for pr_err(), pr_warn(), etc. (shared with the M33 build)
set(LOG_LEVEL WARN CACHE STRING "Console log level")
include(cmake/log_levels.cmake)
enable_logging()

set(MP2_CMSIS_DEVICE_DIR ${PROJECT_SOURCE_DIR}/lib/cmsis-device/stm32mp257d)
set(MP2_CMSIS_CORE_DIR ${PROJECT_SOURCE_DIR}/lib/cmsis)
set(MP2_HAL_DIR ${PROJECT_SOURCE_DIR}/lib/stm32-hal/stm32mp2)

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

# Include paths for HAL, CMSIS, and mdrivlib, used by every target. Same name as MP1's, since shared
# CMakeLists (e.g. src/hardware_support) link to it.
# (An INTERFACE target, since linking an OBJECT library into a static library would copy its objects.)
add_library(mdrivlib_interface INTERFACE)
target_include_directories(mdrivlib_interface INTERFACE
  src/core_a35
  ${MP2_HAL_DIR}/Inc
  ${MP2_CMSIS_CORE_DIR}/Include
  ${MP2_CMSIS_CORE_DIR}/Core_A/Include
  ${MP2_CMSIS_DEVICE_DIR}/Include
  ${MDRIVLIB}
  ${MDRIVLIB}/target/stm32mp2
  ${MDRIVLIB}/target/stm32mp2_ca35
  lib/cpputil
)

add_library(mp2_hal OBJECT ${MP2_HAL_MODULES})
target_link_libraries(mp2_hal PUBLIC mdrivlib_interface)
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
target_link_libraries(mp2_mdrivlib PUBLIC mdrivlib_interface)

#
# LVGL (same library and config as MP1, with MP2 overrides in src/core_a35/lv_conf.h)

set(LV_CONF_PATH ${PROJECT_SOURCE_DIR}/src/core_a35/lv_conf.h CACHE STRING "" FORCE)
add_subdirectory(lib/lvgl ${CMAKE_CURRENT_BINARY_DIR}/lvgl)
target_link_libraries(lvgl PRIVATE mdrivlib_interface)

target_include_directories(lvgl PRIVATE lib/fatfs/source src/fs/fatfs)

#
# MetaModule GUI: SquareLine Studio export (screens, fonts, images) and its C++ helpers

add_subdirectory(src/gui/slsexport ${CMAKE_CURRENT_BINARY_DIR}/slsexport)
target_include_directories(ui_lvgl PRIVATE lib)

#
# App libraries: the same ones MP1's A7 app uses (src/CMakeLists.txt), except the vcv_ports brands
# (none are BUILD_INTERNAL_ yet) and the dynamic plugin loader

set(LIBDIR ${FWDIR}/lib)

add_subdirectory(lib/thorvg ${CMAKE_CURRENT_BINARY_DIR}/thorvg)

# VCV Rack adaptor
add_subdirectory(vcv_plugin ${CMAKE_CURRENT_BINARY_DIR}/vcv_plugin)

# 4ms modules
add_subdirectory(lib/CoreModules/4ms ${CMAKE_CURRENT_BINARY_DIR}/CoreModules-4ms)
target_link_libraries(CoreModules-4ms PRIVATE ThorVG)

# Patch format and serialization
add_subdirectory(lib/patch-serial ${CMAKE_CURRENT_BINARY_DIR}/patch-serial)

if(NOT TARGET jansson)
  add_subdirectory(lib/jansson ${CMAKE_CURRENT_BINARY_DIR}/jansson)
endif()

add_subdirectory(lib/CoreModules ${CMAKE_CURRENT_BINARY_DIR}/CoreModules)

if(NOT TARGET cpputil::cpputil)
  add_subdirectory(lib/cpputil ${CMAKE_CURRENT_BINARY_DIR}/cpputil)
endif()

add_subdirectory(coreproc_plugin ${CMAKE_CURRENT_BINARY_DIR}/coreproc_plugin)


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
# cores link), followed by .sharedmem (the objects). Every buffer the A35 asks the M33 to read a
# file into (or write one from) must be in here.
# Whole 2MB blocks: the A35 MMU maps it in 2MB blocks.
set(SHAREDMEM_ADDR 0x9A000000)
set(SHAREDMEM_SIZE 0x2000000)

include(ExternalProject)
ExternalProject_Add(
  core_m33
  SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/core_m33
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
# A35 application: MP1's A7 app (src/CMakeLists.txt), minus what MP2 doesn't have yet
# (audio, plugins, USB, WiFi, OSPI flash)

# Git commit hash (git_version.h)
include(cmake/CheckGit.cmake)
CheckGitSetup()

# Same as MP1's hardware_support (system API for plugins), with MP2 versions of the hardware parts
add_library(hardware_support STATIC
  src/core_a35/hardware_support/random.cc
  src/core_a35/hardware_support/memory.cc
  src/hardware_support/time.cc
  src/hardware_support/filesystem_helpers.cc
)
target_link_libraries(hardware_support PRIVATE mdrivlib_interface)
target_compile_options(hardware_support PRIVATE -fno-function-sections -fno-data-sections)

set(METAMODULE_FW_DIR ${FWDIR})
include(src/shared_sources.cmake)

add_library(
  a35_core OBJECT
  src/core_a35/main.cc
  src/core_a35/system_init.cc
  src/core_a35/m33_firmware.S
  src/core_a35/assets_image.S
  src/core_a35/uart_print.c
  src/core_a35/async_thread_control.cc
  src/core_a35/console.cc
  src/core_a35/static_buffers.cc
  src/core_a35/no_plugins.cc
  src/core_a35/gettimeofday.cc
  src/core_a35/no_file_syscalls.cc
  vcv_ports/glue/plugin_instance.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/drivers/cycle_counter.cc
  ${MM_SHARED_CORE_SOURCES}
  ${MM_SHARED_APP_SOURCES}
  src/gui/pages/file_browser/file_browser_adaptor.cc
  src/fs/fatfs/fattime.cc
  src/mp2-stubs/dynload/exidx_registry.cc
  system/mmu_ca35.cc
  system/sbrk_mp2.cc
  system/eh_frame_ca35.cc
  system/syscall_stubs_mp2.c
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/startup_ca35.s
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/vectors.S
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/irq_init.c
  ${MDRIVLIB}/target/stm32mp2_ca35/boot/esr_decode.cc
  ${MDRIVLIB}/target/stm32mp2_ca35/drivers/interrupt_handler.cc
  system/libc_stub.c
  ${CMAKE_BINARY_DIR}/checkgit/git_version.cpp
)

target_link_libraries(
  a35_core
  PUBLIC mdrivlib_interface
         lvgl::lvgl
         ui_lvgl
         CoreModules
         "$<LINK_LIBRARY:WHOLE_ARCHIVE,CoreModules-4ms>"
         "$<LINK_LIBRARY:WHOLE_ARCHIVE,coreproc_plugin_export>"
         "$<LINK_LIBRARY:WHOLE_ARCHIVE,hardware_support>"
         metamodule::patch-serial
         cpputil
         ThorVG
         vcv_plugin
)
add_dependencies(a35_core core_m33)
target_compile_definitions(
  a35_core PRIVATE M33_LOAD_ADDR=${M33_LOAD_ADDR} M33_REGION_SIZE=${M33_REGION_SIZE} SHAREDMEM_ADDR=${SHAREDMEM_ADDR}
                   SHAREDMEM_SIZE=${SHAREDMEM_SIZE}
)
target_compile_definitions(a35_core PUBLIC CPPUTIL_STATIC_STRING_USE_STD_STRING SUPPRESS_HIL_MESSAGES=1)
set_source_files_properties(
  src/core_a35/m33_firmware.S PROPERTIES COMPILE_DEFINITIONS "M33_FIRMWARE_BIN=\"${M33_BIN}\"" OBJECT_DEPENDS ${M33_BIN}
)
# The assets image is embedded in the firmware image (src/core_a35/assets_image.S), since MP2 can't
# read it from flash yet. The MP2 build doesn't make one yet: it uses the MP1 build's.
set(MP2_ASSETS_UIMG ${FWDIR}/build/assets.uimg CACHE FILEPATH "Assets image to embed in the firmware")
if(EXISTS ${MP2_ASSETS_UIMG})
  set_source_files_properties(
    src/core_a35/assets_image.S PROPERTIES COMPILE_DEFINITIONS "ASSETS_IMAGE=\"${MP2_ASSETS_UIMG}\"" OBJECT_DEPENDS
                                           ${MP2_ASSETS_UIMG}
  )
else()
  message(WARNING "No assets image at ${MP2_ASSETS_UIMG}: the firmware will have no module images or fonts. "
                  "Build MP1 first (cmake --preset full && cmake --build --preset full), then re-run cmake.")
endif()
# LVGL's headers OR together values from different enums (deprecated in C++20); MP1 silences this too
target_compile_options(
  a35_core PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion -Wno-deprecated-anon-enum-enum-conversion>
)

target_include_directories(
  a35_core
  PUBLIC src/mp2-stubs # first: stands in for drivers and features MP2 doesn't have yet
         src/pro # before src, so pro's conf/ headers are found before the shared ones in src/conf/
         src
         .
         src/console
         src/params
         src/fs
         lib
         lib/fatfs/source
         src/fs/fatfs
         vcv_ports
         vcv_ports/glue
         vcv_ports/glue/ext_plugin
         ${CMAKE_BINARY_DIR}/checkgit
)

# (Linking the a35_core OBJECT library adds its objects, and the libraries it links)
add_executable(main_a35.elf $<TARGET_OBJECTS:mp2_mdrivlib> $<TARGET_OBJECTS:mp2_hal>)
target_link_libraries(main_a35.elf PRIVATE a35_core)

set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/system/linker/stm32mp2xx_ca35.ld)
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

#
# Flashing

add_custom_target(
  flash-t32
  DEPENDS main_a35.elf
  COMMENT "Reset, load, and boot via TRACE32"
  COMMAND python3 flashing/flash-t32-mp2.py $<TARGET_FILE:main_a35.elf>
  VERBATIM USES_TERMINAL
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# TODO (in bring-up order):
# - image packaging: FIP for TF-A BL2 (successor of flashing/elf_to_uimg.py)
# - port src/medium/conf headers into src/pro/conf as each subsystem
#   comes up; then start compiling src/shared_sources.cmake lists here
