add_library(nanovg STATIC)

if(DEFINED METAMODULE_HEADLESS)
  target_sources(nanovg PRIVATE nanovg_stubs.c)
  target_compile_options(nanovg PRIVATE $<$<CXX_COMPILER_ID:GNU>: $<$<COMPILE_LANGUAGE:C>:-Wno-uninitialized> >)
else()
  target_sources(nanovg PRIVATE nanovg.c)
  target_link_libraries(nanovg PRIVATE ThorVG)
  target_compile_options(nanovg PRIVATE $<$<CXX_COMPILER_ID:GNU>: $<$<COMPILE_LANGUAGE:C>:-Wno-stringop-overflow> >)
endif()

set_property(TARGET nanovg PROPERTY CXX_STANDARD 23)

target_include_directories(nanovg PRIVATE ./)

target_compile_definitions(nanovg PRIVATE METAMODULE)
