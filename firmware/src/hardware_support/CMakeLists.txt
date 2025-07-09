cmake_minimum_required(VERSION 3.24)
project(hardware-support)

add_library(hardware_support STATIC)

target_sources(hardware_support PRIVATE
	random.cc
	time.cc
)

target_link_libraries(hardware_support PRIVATE 
	mdrivlib_interface
)

target_compile_options(hardware_support PRIVATE 
	-fno-function-sections 
	-fno-data-sections
)

set_target_properties(hardware_support PROPERTIES CXX_STANDARD 23)

