cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(AirwindowsPlugin
    VERSION 0.1 
    DESCRIPTION "Airwindows Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(Airwin2RackLibrary STATIC)

target_include_directories(Airwin2RackLibrary PRIVATE 
	. 
    ../../airwin2rack/src
)

target_sources(Airwin2RackLibrary PRIVATE
	airwin_modules.cc
)

target_compile_definitions(Airwin2RackLibrary PRIVATE 
	DISABLE_CONSOLE
)

add_subdirectory(../../airwin2rack ${CMAKE_CURRENT_BINARY_DIR}/airwin2rack)
target_compile_options(airwin-registry PRIVATE "-Wno-misleading-indentation;-Wno-unused-variable;-Wno-stringop-truncation")

target_link_libraries(Airwin2RackLibrary PUBLIC airwin-registry)

if (BUILD_DYN_PLUGIN)
	# Call this to link and create the plugin file
	create_plugin(
		SOURCE_LIB      Airwin2RackLibrary
		PLUGIN_NAME     Airwin2Rack                  # This must match the brand "slug" used in VCV Rack
		SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
		DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Airwin2Rack
	)
endif()

