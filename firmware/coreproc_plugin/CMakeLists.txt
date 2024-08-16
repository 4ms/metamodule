cmake_minimum_required(VERSION 3.24)
project(CoreProc-Plugin)

add_library(coreproc_plugin_export STATIC)

target_sources(coreproc_plugin_export PRIVATE
    create.cc
)

target_include_directories(coreproc_plugin_export PRIVATE
    # ${CMAKE_CURRENT_LIST_DIR}/../lib
)

target_link_libraries(coreproc_plugin_export PRIVATE 
	cpputil 
	metamodule::core-interface
	CoreModules
)

target_compile_options(coreproc_plugin_export PRIVATE 
	-fno-function-sections 
	-fno-data-sections
)

set_target_properties(coreproc_plugin_export PROPERTIES CXX_STANDARD 23)
