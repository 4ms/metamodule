#
# Internal vcv_plugin library (symbols not exported)
#

set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)
set(SHARED ${MM_ROOT}/shared)

add_library(vcv_plugin_internal STATIC 
    make_element.cc
    svg.cc
)

target_include_directories(vcv_plugin_internal PRIVATE 
    ../export 
    ${SHARED} 
    ${MM_ROOT}/firmware/src
)

target_link_libraries(vcv_plugin_internal PRIVATE 
    cpputil 
    metamodule::core-interface 
    metamodule::rack-interface
    lvgl::lvgl
)

set_source_files_properties(svg.cc 
    PROPERTIES 
    COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)



