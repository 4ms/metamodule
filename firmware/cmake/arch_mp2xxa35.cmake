macro(set_arch_flags)
add_compile_definitions(
      USE_HAL_DRIVER
      USE_FULL_LL_DRIVER
      STM32MP2
      STM32MP257Cxx
      CORE_CA35
      __AARCH64__
)

# Note: MCU_FLAGS is used with linking as well
set(MCU_FLAGS
    -fno-exceptions
    -fno-math-errno
    -mcpu=cortex-a35
    -mlittle-endian
    -mfpu=neon-fp-armv8
    -mfloat-abi=hard
    # -mthumb-interwork
    #-mstrict-align
    -mno-unaligned-access
    -mtune=cortex-a35
    -mvectorize-with-neon-quad
    -funsafe-math-optimizations
)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(
  ${MCU_FLAGS}
  # -nostdlib
  "SHELL:--param l1-cache-size=32"
  "SHELL:--param l1-cache-line-size=64"
  "SHELL:--param l2-cache-size=512"
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
  -Wall
  -Werror=return-type
  -Wsign-compare
  -Wno-psabi
  "$<$<COMPILE_LANGUAGE:CXX>:-ffold-simple-inlines>"
  "$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
)

set(LINK_OPTIONS
#     -L${CMAKE_CURRENT_LIST_DIR}/../system/newlib
#     -lc
#     -lg
#     -lm
)

add_link_options(${MCU_FLAGS} ${LINK_OPTIONS})
endmacro()
