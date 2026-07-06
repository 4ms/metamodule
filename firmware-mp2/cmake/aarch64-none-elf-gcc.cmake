set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_BASE_DIR "" CACHE FILEPATH "Location of toolchain 'bin' directory")

# Default is the bare-metal aarch64-none-elf toolchain (same as stm32mp2-baremetal).
# Override TOOLCHAIN_TRIPLE for CI environments that only have aarch64-linux-gnu
# (compiles fine; final link needs newlib, i.e. the none-elf toolchain).
set(TOOLCHAIN_TRIPLE "aarch64-none-elf" CACHE STRING "Cross-toolchain triple")

if (TOOLCHAIN_BASE_DIR)
  set(TOOLCHAIN_PREFIX "${TOOLCHAIN_BASE_DIR}/${TOOLCHAIN_TRIPLE}-")
else()
  set(TOOLCHAIN_PREFIX "${TOOLCHAIN_TRIPLE}-")
endif()

set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE_UTIL    ${TOOLCHAIN_PREFIX}size    CACHE INTERNAL "size tool")
find_program(CMAKE_GDB ${TOOLCHAIN_PREFIX}gdb gdb CACHE INTERNAL "gdb client")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(CMAKE_AR ${TOOLCHAIN_PREFIX}gcc-ar)

set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE
"-Wl,--whole-archive" "<LINK_ITEM>" "-Wl,--no-whole-archive"
)
set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE_SUPPORTED True)
