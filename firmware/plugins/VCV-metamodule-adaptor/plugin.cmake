set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/arm-none-eabi-gcc.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")

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
	"$<$<COMPILE_LANGUAGE:CXX>:-Wno-register>"
	"$<$<COMPILE_LANGUAGE:CXX>:-Wno-volatile>"
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


add_library(mm_vcv_plugin STATIC ${CMAKE_CURRENT_LIST_DIR}/libc_stub.c)

target_compile_options(mm_vcv_plugin PUBLIC
	-shared
	-fPIC
	-nostartfiles
	-nostdlib
)

target_include_directories(mm_vcv_plugin PUBLIC
    SYSTEM
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/dep/include
    ${CMAKE_CURRENT_LIST_DIR}/dep/include/cpputil
)

set_property(TARGET mm_vcv_plugin PROPERTY CXX_STANDARD 23)
target_link_libraries(mm_vcv_plugin PUBLIC arch_mp15x_a7)

set(LFLAGS
    -shared
    ${MCU_FLAGS}
    -Wl,-Map,plugin.map,--cref
    -Wl,--gc-sections
    -nostartfiles -nostdlib
)


macro(create_plugin)

    set(PLUGIN ${arg1})

    # target_link_libraries(${PLUGIN} PRIVATE mm_vcv_plugin)

    target_link_options(${PLUGIN} PRIVATE 
        -shared
        ${MCU_FLAGS}
        -Wl,-Map,plugin.map,--cref
        -Wl,--gc-sections
        -nostartfiles -nostdlib
    )

    add_custom_command(
            OUTPUT ${PLUGIN}-debug.so
            DEPENDS ${PLUGIN}
            COMMAND ${CMAKE_CXX_COMPILER} ${LFLAGS} -o ${PLUGIN}-debug.so $<TARGET_OBJECTS:${PLUGIN}> $<TARGET_OBJECTS:mm_vcv_plugin>
            COMMAND_EXPAND_LISTS
            VERBATIM USES_TERMINAL
        )

        add_custom_command(
            OUTPUT ${PLUGIN}.so
            DEPENDS ${PLUGIN}-debug.so
            COMMAND ${CMAKE_STRIP} -g -v -o ${PLUGIN}.so ${PLUGIN}-debug.so
            VERBATIM USES_TERMINAL
        )

        add_custom_target(
            plugin
            ALL
            DEPENDS ${PLUGIN}.so
        )

    endmacro()


