add_library(nanovg STATIC)

target_sources(nanovg PRIVATE nanovg.c)

set_property(TARGET nanovg PROPERTY CXX_STANDARD 23)

target_include_directories(nanovg PRIVATE ./)

target_compile_definitions(nanovg PRIVATE METAMODULE)

target_link_libraries(nanovg PRIVATE ThorVG)

target_compile_options(nanovg PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wno-stringop-overflow>)
