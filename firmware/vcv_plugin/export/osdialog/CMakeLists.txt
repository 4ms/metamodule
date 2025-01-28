add_library(osdialog STATIC)

target_sources(osdialog PRIVATE 
    osdialog.c
    osdialog-mm.cc
    async_filebrowser.cc
)

set_property(TARGET osdialog PROPERTY CXX_STANDARD 23)

target_include_directories(osdialog PRIVATE 
    ${FWDIR}/src
    ${FWDIR}/src/console
)

target_link_libraries(osdialog PRIVATE 
    metamodule::rack-interface 
    metamodule::core-interface 
    metamodule-patch-serial
    mdrivlib_interface
    cpputil 
    lvgl
)

# target_compile_definitions(osdialog PRIVATE)
