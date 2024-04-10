include(modules.cmake)

add_library(eightfoldLibrary OBJECT ${EIGHTFOLD_SOURCE_PATHS}
)

target_include_directories(eightfoldLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../eightfold/src)

target_compile_options(eightfoldLibrary PRIVATE -Wno-double-promotion)

set_property(TARGET eightfoldLibrary PROPERTY CXX_STANDARD 20)
