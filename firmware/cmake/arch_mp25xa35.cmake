# Arch flags for the STM32MP25x Cortex-A35 (AArch64)
# Execution model: EL3 secure (matches mdrivlib target/stm32mp2_ca35)

macro(set_arch_flags)
add_compile_definitions(
      USE_HAL_DRIVER
      USE_FULL_LL_DRIVER
      STM32MP2
      STM32MP257Dxx
      CORE_CA35
      CORTEX_IN_SECURE_STATE
      RUN_EL3
)
# USE_HAL_DRIVER pulls in src/core_a35/stm32mp2xx_hal_conf.h (via stm32mp2xx.h)

# Note: MCU_FLAGS is used with linking as well
# Exceptions and RTTI are on, as on MP1's A7 (ryml reports parse errors by throwing, and the
# Rack adaptor uses dynamic_cast)
set(MCU_FLAGS
    -fno-math-errno
    -mcpu=cortex-a35
    -march=armv8-a+fp+simd
    -mtune=cortex-a35
    -mlittle-endian
    -funsafe-math-optimizations
)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(
  ${MCU_FLAGS}
  -nostdlib
  "$<$<CONFIG:Debug>:-O0>"
  "$<$<CONFIG:Debug>:-g3>"
  "$<$<CONFIG:Release>:-Ofast>"
  "$<$<CONFIG:RelWithDebInfo>:-Ofast>"
  "$<$<CONFIG:RelWithDebInfo>:-g3>"
  -fno-common
  -fdata-sections
  -ffunction-sections
  -nostartfiles
  -Wall
  -Werror=return-type
  -Wsign-compare
  -Wno-psabi
  "$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
)

add_link_options(
  ${MCU_FLAGS}
  -Wl,--gc-sections
  -nostartfiles
)
endmacro()
