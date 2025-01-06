cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MetaModuleHeadless LANGUAGES C CXX)

set(SIMULATOR 1)
set(METAMODULE_HEADLESS 1)

set(FWDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware)
set(LIBDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware/lib)

add_compile_options(-O3 -g2)
include(${FWDIR}/cmake/log_levels.cmake)
enable_logging()

# #################### cpputil #########################################

add_subdirectory(${LIBDIR}/cpputil cpputil)
target_compile_definitions(cpputil PUBLIC CPPUTIL_STATIC_STRING_USE_STD_STRING)


# #################### RYML ##################################

add_subdirectory(${LIBDIR}/patch-serial ${CMAKE_CURRENT_BINARY_DIR}/patch-serial)


# #################### VCV Adaptor ##################################

add_subdirectory(${FWDIR}/vcv_plugin ${CMAKE_CURRENT_BINARY_DIR}/vcv_plugin)

# #################### Other brands ##################################
 
add_subdirectory(${FWDIR}/vcv_ports/ ${CMAKE_CURRENT_BINARY_DIR}/vcv_ports)
target_compile_options(vcv_ports INTERFACE -Wno-double-promotion)

# #################### Application ############################################

add_subdirectory(${LIBDIR}/CoreModules ${CMAKE_CURRENT_BINARY_DIR}/CoreModules)
add_subdirectory(${LIBDIR}/CoreModules/4ms ${CMAKE_CURRENT_BINARY_DIR}/CoreModules-4ms)
target_compile_options(CoreModules INTERFACE -Wno-double-promotion)


add_executable(
    simulator 
    src/main.cc 
    stubs/svg.cc
    stubs/random.cpp

	${FWDIR}/coreproc_plugin/create.cc

	${FWDIR}/metamodule-plugin-sdk/version.cc
    )

target_include_directories(
  simulator
  PRIVATE src
          stubs
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/medium
		  ${FWDIR}
            .
          )

target_compile_options(simulator PRIVATE -Wall -Og)
target_compile_options(simulator PRIVATE -Wno-double-promotion)

# Workaround for std::expected not available in clang
# https://www.reddit.com/r/cpp/comments/1b6f3s4/any_news_on_when_libc_is_going_to_support/
# https://github.com/llvm/llvm-project/issues/62801

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(simulator PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:-D__cpp_concepts=202002>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-builtin-macro-redefined>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-macro-redefined>
  )
endif()


target_link_libraries(simulator PRIVATE 
	metamodule::patch-serial
	vcv_ports
)
target_link_libraries(simulator PUBLIC "$<LINK_LIBRARY:WHOLE_ARCHIVE,CoreModules-4ms>")
target_link_libraries(simulator PUBLIC "$<LINK_LIBRARY:WHOLE_ARCHIVE,vcv_plugin_internal>")
target_link_libraries(simulator PUBLIC "$<LINK_LIBRARY:WHOLE_ARCHIVE,vcv_plugin_export>")

target_compile_definitions(simulator PUBLIC SIMULATOR)

set_property(TARGET simulator PROPERTY CXX_STANDARD 23)

# Arch-dependent Link options:
message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_options(simulator PUBLIC "-Wl,-map,simulator.map")
  else()
    target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(simulator PRIVATE "/MAP:simulator.map")
endif()


## Debugging
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang") 
  find_program(CMAKE_DEBUGGER_BINARY lldb)
  set(DEBUG_COMMAND ${CMAKE_DEBUGGER_BINARY} $<TARGET_FILE:simulator> -- 
    --sdcarddir ${CMAKE_CURRENT_LIST_DIR}/patches
    --flashdir ${CMAKE_CURRENT_LIST_DIR}/../patches/default
    --assets ${CMAKE_CURRENT_LIST_DIR}/build/assets.uimg
  )


elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  find_program(CMAKE_DEBUGGER_BINARY gdb)
  set(DEBUG_COMMAND ${CMAKE_DEBUGGER_BINARY} -q
    -ex \"set debuginfod enabled off\"
    -ex \"set pagination off\" 
    -ex \"run\"
    --args $<TARGET_FILE:simulator> 
    --sdcarddir ${CMAKE_CURRENT_LIST_DIR}/patches
    --flashdir ${CMAKE_CURRENT_LIST_DIR}/../shared/patch/default
    --assets ${CMAKE_CURRENT_LIST_DIR}/build/assets.uimg
  )
else ()
  set(DEBUG_COMMAND echo "Compiler is ${CMAKE_CXX_COMPILER_ID}, but must be Clang, AppleClang, or GNU to debug")
endif()

add_custom_target(
  debug
  DEPENDS simulator
  COMMAND ${DEBUG_COMMAND}
  USES_TERMINAL
)

include(ext-plugins.cmake)
