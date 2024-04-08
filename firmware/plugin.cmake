add_library(arch_mp15x_a7 INTERFACE)

target_compile_definitions(arch_mp15x_a7 INTERFACE
	USE_HAL_DRIVER
	USE_FULL_LL_DRIVER
	STM32MP1
	STM32MP157Cxx
	CORE_CA7
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

target_compile_options(arch_mp15x_a7 INTERFACE
	${MCU_FLAGS}
	"SHELL:--param l1-cache-size=32"
	"SHELL:--param l1-cache-line-size=64"
	"SHELL:--param l2-cache-size=256"
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
	-Wno-psabi
	-Wno-double-promotion
	-Wno-attributes
	-Wno-register
	-Wno-volatile
	"$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>"
	"$<$<COMPILE_LANGUAGE:CXX>:-ffold-simple-inlines>"
	"$<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>"
)

target_link_options(arch_mp15x_a7 
	INTERFACE 
	${MCU_FLAGS}
	-Wl,--gc-sections 
	-nostartfiles 
	-nostdlib
)

# -Wl,-Map,$(PLUGINNAME).map,--cref


add_library(mm_vcv_plugin STATIC libc_stub.c)

target_compile_options(mm_vcv_plugin PUBLIC
	-shared
	-fPIC
	-nostartfiles
	-nostdlib
)

set_property(TARGET mm_vcv_plugin PROPERTY CXX_STANDARD 23)
target_link_libraries(mm_vcv_plugin PUBLIC arch_mp15x_a7)
