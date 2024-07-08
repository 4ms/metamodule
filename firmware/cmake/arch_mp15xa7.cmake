macro(set_arch_flags)
add_compile_definitions(
      USE_HAL_DRIVER
      USE_FULL_LL_DRIVER
      STM32MP1
      STM32MP157Cxx
      CORE_CA7
      $<$<BOOL:${USE_FEWER_MODULES}>:USE_FEWER_MODULES=1>
)

# Note: MCU_FLAGS is used with linking as well
set(MCU_FLAGS
    -fno-exceptions
    -fno-math-errno
    -mcpu=cortex-a7
    -mlittle-endian
    -mfpu=neon-vfpv4
    -mfloat-abi=hard
    -mthumb-interwork
    -mno-unaligned-access
    -mtune=cortex-a7
    -mvectorize-with-neon-quad
    -funsafe-math-optimizations
)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(
  ${MCU_FLAGS}
  "SHELL:--param l1-cache-size=32"
  "SHELL:--param l1-cache-line-size=64"
  "SHELL:--param l2-cache-size=256"
  "$<$<CONFIG:Debug>:-O0>"
  "$<$<CONFIG:Debug>:-g3>"
  "$<$<CONFIG:Release>:-Ofast>"
  "$<$<CONFIG:RelWithDebInfo>:-Ofast>"
  "$<$<CONFIG:RelWithDebInfo>:-g3>"
  -fno-common
  -fdata-sections
  -ffunction-sections
  -nostartfiles
  -ffreestanding
  -fno-unwind-tables
  -Wall
  -Werror=return-type
  -Wsign-compare
  -Wno-psabi
  "$<$<COMPILE_LANGUAGE:CXX>:-ffold-simple-inlines>"
  "$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
)

add_link_options(${MCU_FLAGS})
endmacro()
