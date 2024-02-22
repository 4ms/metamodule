project(sls_export)

file(STRINGS ${CMAKE_CURRENT_LIST_DIR}/filelist.txt SOURCES)

add_library(ui ${SOURCES})
target_link_libraries(ui PUBLIC lvgl)

# Fix for SLS generated files (See https://forum.squareline.io/t/unused-variable-target-warning-when-compiling/1610/3 )
target_compile_options(ui PRIVATE -Wno-unused-variable)
