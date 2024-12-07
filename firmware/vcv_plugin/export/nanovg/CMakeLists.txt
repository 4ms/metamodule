add_library(nanovg STATIC)

target_sources(nanovg PRIVATE 
    nanovg.c 
)

set_property(TARGET nanovg PROPERTY CXX_STANDARD 23)

target_include_directories(nanovg PRIVATE ./)

target_compile_definitions(nanovg PRIVATE)
