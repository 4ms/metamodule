#
# Internal vcv_plugin library (symbols not exported)
#

set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

add_library(vcv_plugin_internal STATIC 
	make_element.cc
)

target_include_directories(vcv_plugin_internal PRIVATE 
	../export 
	${MM_ROOT}/firmware/lib
	${MM_ROOT}/firmware/src
)

target_link_libraries(vcv_plugin_internal PRIVATE 
	cpputil 
	metamodule::core-interface 
	metamodule::rack-interface
)

if (NOT DEFINED METAMODULE_HEADLESS)
	target_link_libraries(vcv_plugin_internal PRIVATE lvgl::lvgl)

	target_sources(vcv_plugin_internal PRIVATE
		svg.cc
		nanovg_pixbuf.cc
		fons-wrapper.cc
	)

	set_source_files_properties(
		svg.cc 
		nanovg_pixbuf.cc 
		PROPERTIES 
		COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
	)
endif()



