set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_BASE_DIR "" CACHE FILEPATH "Location of toolchain 'bin' directory")

if (TOOLCHAIN_BASE_DIR)
  set(TOOLCHAIN_PREFIX "${TOOLCHAIN_BASE_DIR}/arm-none-eabi-")
else()
  set(TOOLCHAIN_PREFIX "arm-none-eabi-")
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

# Handle static libraries through compiler
# This is required to work with static libraries that contain LTO data
# TODO: needs to be implemented for clang
SET(CMAKE_AR  ${TOOLCHAIN_PREFIX}gcc-ar)

# Backport cmake whole linking to cross toolchain
# TODO: needs to be added for clang
set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE 
"-Wl,--whole-archive" "<LINK_ITEM>" "-Wl,--no-whole-archive"
)
set(CMAKE_LINK_LIBRARY_USING_WHOLE_ARCHIVE_SUPPORTED True)
