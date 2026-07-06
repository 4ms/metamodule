# Arch flags for the STM32MP25x Cortex-A35 (AArch64), modeled on
# firmware/cmake/arch_mp15xa7.cmake and stm32mp2-baremetal/shared/makefile-common.mk.
# Execution model: EL3 secure (matches mdrivlib target/stm32mp2_ca35 and the
# verified baremetal examples).

macro(set_arch_flags)
add_compile_definitions(
      USE_FULL_LL_DRIVER
      STM32MP2
      STM32MP257Cxx
      CORE_CA35
      CORTEX_IN_SECURE_STATE
      RUN_EL3
)
# Note: USE_HAL_DRIVER is added per-target once a stm32mp2xx_hal_conf.h exists
# for this project (the HAL-based drivers -- SAI, I2C, HPDMA -- need it).

# Note: MCU_FLAGS is used with linking as well
set(MCU_FLAGS
    -fno-exceptions
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
  -fno-unwind-tables
  -ffreestanding
  -Wall
  -Werror=return-type
  -Wsign-compare
  -Wno-psabi
  "$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>"
  "$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
)

add_link_options(
  ${MCU_FLAGS}
  -Wl,--gc-sections
  -nostartfiles
)
endmacro()
