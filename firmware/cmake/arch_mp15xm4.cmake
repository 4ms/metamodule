macro(set_arch_flags)
add_compile_definitions(
    USE_HAL_DRIVER
    USE_FULL_LL_DRIVER
    STM32MP157Cxx
    STM32MP1
    CORE_CM4
    ARM_MATH_CM4
)

# Note: MCU_FLAGS is used with linking as well
set(MCU_FLAGS
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
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
  $<$<COMPILE_LANGUAGE:CXX>:-ffold-simple-inlines>
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
