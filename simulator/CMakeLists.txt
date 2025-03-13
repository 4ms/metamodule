cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(metamodule-simulator LANGUAGES C CXX)

set(SIMULATOR 1)
option(HEADLESS "Build as headless" OFF)

set(FWDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware)
set(LIBDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware/lib)

if (HEADLESS)
	message("Building Headless")

	add_compile_options(
		-Ofast
		-ffast-math
		-funsafe-math-optimizations
	)
	set(METAMODULE_HEADLESS 1)

else()

	message("Building Simulator with GUI")

	add_compile_options(-O0 -g2)

	add_compile_definitions(SIMULATOR)

	set(LVGL_DIR ${FWDIR}/lib/lvgl/lvgl)

	set(LV_CONF_PATH
		${CMAKE_CURRENT_LIST_DIR}/lv_conf.h
		CACHE STRING "" FORCE)

endif()

include(${FWDIR}/cmake/log_levels.cmake)
enable_logging()

# #################### cpputil #########################################

add_subdirectory(${LIBDIR}/cpputil cpputil)
target_compile_definitions(cpputil PUBLIC CPPUTIL_STATIC_STRING_USE_STD_STRING)



# #################### LVGL Simulator Driver #################################

if (NOT HEADLESS)
	add_subdirectory(lvgl_drv)
endif()

# #################### LVGL ############################################

if (NOT HEADLESS)
	get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)
	include(${LVGL_DIR}/CMakeLists.txt)
	target_include_directories(lvgl PRIVATE 
			  ${FWDIR}/lib/fatfs/source
			  ${FWDIR}/src/fs/fatfs
	)

endif()

# #################### RYML ##################################

add_subdirectory(${LIBDIR}/patch-serial ${CMAKE_CURRENT_BINARY_DIR}/patch-serial)

# #################### SLS Export ##################################
if (NOT HEADLESS)
	add_subdirectory(${FWDIR}/src/gui/slsexport/meta5 ${CMAKE_CURRENT_BINARY_DIR}/ui)
	target_link_libraries(ui PRIVATE lvgl)
endif()

# #################### VCV Adaptor ##################################

add_subdirectory(${FWDIR}/vcv_plugin ${CMAKE_CURRENT_BINARY_DIR}/vcv_plugin)

# #################### Other brands ##################################
 
add_subdirectory(${FWDIR}/vcv_ports/ ${CMAKE_CURRENT_BINARY_DIR}/vcv_ports)
target_compile_options(vcv_ports INTERFACE -Wno-double-promotion)

# #################### Application ############################################

add_subdirectory(${LIBDIR}/CoreModules ${CMAKE_CURRENT_BINARY_DIR}/CoreModules)
add_subdirectory(${LIBDIR}/CoreModules/4ms ${CMAKE_CURRENT_BINARY_DIR}/CoreModules-4ms)
target_compile_options(CoreModules INTERFACE -Wno-double-promotion)

if(HEADLESS)
	add_executable(simulator 
		src/headless/main-headless.cc 
		src/headless/audio_files.cc 
		stubs/svg.cc
		stubs/random.cpp

		${FWDIR}/coreproc_plugin/create.cc

		${FWDIR}/metamodule-plugin-sdk/version.cc
		)
else()
	add_executable(simulator 
		src/main.cc 
		src/ui.cc
		stubs/random.cpp
		stubs/memory/heap.cc
		${FWDIR}/src/gui/elements/element_name.cc
		${FWDIR}/src/gui/slsexport/ui_local.cc
		${FWDIR}/src/gui/slsexport/prefs_pane_fs.cc
		${FWDIR}/src/gui/fonts/fonts.cc
		${FWDIR}/src/fw_update/updater_proxy.cc
		${FWDIR}/src/patch_play/modules_helpers.cc
		${FWDIR}/src/params/expanders.cc
        ${FWDIR}/src/patch_file/reload_patch.cc

		#Fatfs:
		stubs/fattime.cc
		${FWDIR}/lib/fatfs/source/ff.c
		${FWDIR}/lib/fatfs/source/ffunicode.c
		${FWDIR}/src/fs/fatfs/diskio.cc
		${FWDIR}/src/fs/fatfs/delete_node.cc
		${FWDIR}/src/fs/time_convert.cc
		${FWDIR}/src/fs/general_io.cc
		#Tar:
		${FWDIR}/src/fs/asset_drive/untar.cc


		${FWDIR}/src/user_settings/settings_file.cc
		${FWDIR}/src/user_settings/settings_parse.cc
		${FWDIR}/src/user_settings/settings_serialize.cc

		${FWDIR}/coreproc_plugin/create.cc

		${FWDIR}/metamodule-plugin-sdk/version.cc
		)
endif()

target_include_directories(
  simulator
  PRIVATE src/headless
  		  src
          stubs
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/medium
		  ${FWDIR}
            .
)

if(NOT HEADLESS)
	target_include_directories(
	  simulator
	  PRIVATE sdl_audio
			  ${FWDIR}/src/params
			  ${FWDIR}/lib/fatfs/source
			  ${FWDIR}/src/fs/fatfs
	)
endif()

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
if(NOT HEADLESS)
	target_link_libraries(simulator PRIVATE 
		${SDL2_LIBRARIES}
		lvglsdl
		SDL2
		ui
	)
endif()

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

include(${FWDIR}/vcv_ports/brands.cmake)
foreach(brand ${brands})
	if (DEFINED BUILD_DYN_PLUGIN_${brand})
	target_compile_definitions(simulator PRIVATE -DBUILD_DYN_PLUGIN_${brand})

	elseif (DEFINED OMIT_BRAND_${brand})
	target_compile_definitions(simulator PRIVATE -DOMIT_BRAND_${brand})

    else()
	target_compile_definitions(simulator PRIVATE -DBUILD_INTERNAL_${brand})
	endif()
endforeach()

include(ext-plugins.cmake)
