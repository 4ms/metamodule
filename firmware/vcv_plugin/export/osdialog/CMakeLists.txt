add_library(osdialog STATIC)

target_sources(osdialog PRIVATE 
    osdialog.c
    osdialog-mm.cc
)

set_property(TARGET osdialog PROPERTY CXX_STANDARD 23)

# target_include_directories(osdialog PRIVATE )
target_link_libraries(osdialog PRIVATE metamodule::rack-interface cpputil lvgl)

# target_compile_definitions(osdialog PRIVATE)
