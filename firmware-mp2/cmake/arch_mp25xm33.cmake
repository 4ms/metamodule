# Arch flags for the STM32MP25x Cortex-M33 coprocessor, modeled on
# firmware/cmake/arch_mp15xm4.cmake. The M33 build is a separate CMake project
# (arm-none-eabi toolchain); this file is included by it, not by the A35 build.
#
# Role (confirmed): the M33 mirrors the MP1 M4 by default -- controls/gate
# jacks, filesystem, wifi -- behind the movable core_intercom abstraction.

macro(set_arch_flags)
add_compile_definitions(
    USE_HAL_DRIVER
    USE_FULL_LL_DRIVER
    STM32MP257Cxx
    STM32MP2
    CORE_CM33
    ARM_MATH_CM33
)

# Note: MCU_FLAGS is used with linking as well
set(MCU_FLAGS
    -mcpu=cortex-m33
    -mfpu=fpv5-sp-d16
    -mthumb
    -mlittle-endian
    -mfloat-abi=hard
    -fno-exceptions
)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(
  ${MCU_FLAGS}
  "$<$<CONFIG:Debug>:-O0>"
  "$<$<CONFIG:Debug>:-g3>"
  "$<$<CONFIG:Release>:-O3>"
  "$<$<CONFIG:RelWithDebInfo>:-O3>"
  "$<$<CONFIG:RelWithDebInfo>:-g3>"
  -fno-common
  -fdata-sections
  -ffunction-sections
  -nostartfiles
  -fno-unwind-tables
  -Wall
  -Werror=return-type
  -Wsign-compare
  -Wdouble-promotion
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
  $<$<COMPILE_LANGUAGE:CXX>:-Wno-psabi>
  $<$<COMPILE_LANGUAGE:CXX>:-Wno-register>
)

add_link_options(
    -Wl,--gc-sections
    -nostartfiles
    ${MCU_FLAGS}
)
endmacro()
