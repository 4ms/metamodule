add_library(nanovg STATIC)

target_sources(nanovg PRIVATE 
    nanovg.c 
    nanovg_gl.cc
)

target_link_libraries(nanovg PRIVATE metamodule-rack-interface)

target_include_directories(nanovg PRIVATE ./)

target_compile_definitions(nanovg PRIVATE)
