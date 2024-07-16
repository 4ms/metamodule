cmake_minimum_required(VERSION 3.24)
project(vcv_ports)

#############################

# TODO: remove hardcoded paths

if (NOT TARGET metamodule::vcv-plugin-interface)
  add_subdirectory(../vcv_plugin/interface vcv-plugin)
endif()

if (NOT TARGET cpputil::cpputil)
  add_subdirectory(../../shared/cpputil cpputil)
endif()

#############################

# Create library that combines all brands
# Link against this library from outside
add_library(_vcv_ports_internal STATIC)

# All built-ins use a common pluginInstance symbol
target_sources(_vcv_ports_internal PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/plugin_instance.cc)

if (CMAKE_CROSSCOMPILING)
  # Enable LTO for top level library
  set_property(TARGET _vcv_ports_internal PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_property(TARGET _vcv_ports_internal PROPERTY CXX_STANDARD 23)


# Create interface wrapper that whole-links the actual library
add_library(vcv_ports INTERFACE)
target_link_libraries(vcv_ports INTERFACE "$<LINK_LIBRARY:WHOLE_ARCHIVE,_vcv_ports_internal>")
target_include_directories(vcv_ports INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Get list of brands
include(${CMAKE_CURRENT_LIST_DIR}/brands.cmake)

foreach(brand ${brands})

  if (BUILD_DYN_PLUGIN_${brand})
	message("Building ${brand} as external plugin")
	include(ExternalProject)
	# TODO: pass installation dir to plugin project. Create a cmake target `install` for the plugin in `plugin.cmake`
	ExternalProject_Add(
		${brand}
		SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/glue/${brand}
		CMAKE_ARGS -DBUILD_DYN_PLUGIN=1
		INSTALL_COMMAND ""
	)

  else()

	message("Building ${brand} as built-in plugin")
	add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glue/${brand})
	target_compile_options(${brand}Library PRIVATE -Wno-attributes $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>)

	# Link against the mocked vcv interface
	target_link_libraries(${brand}Library PRIVATE metamodule::vcv-plugin-interface)

	target_link_libraries(${brand}Library PRIVATE cpputil::cpputil)

	if (CMAKE_CROSSCOMPILING)
		# Enable LTO for all brands
		set_property(TARGET ${brand}Library PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
	endif()

	target_link_libraries(_vcv_ports_internal PUBLIC ${brand}Library)

	endif()

endforeach()

