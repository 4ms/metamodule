cmake_minimum_required(VERSION 3.24)
project(CoreProc-Plugin)

set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../)

add_library(coreproc_plugin_export STATIC)

target_sources(coreproc_plugin_export PRIVATE
    create.cc
)

target_include_directories(coreproc_plugin_export PRIVATE
    ${MM_ROOT}/firmware/lib
    ${MM_ROOT}/firmware/metamodule-plugin-sdk/metamodule-core-interface
    ${MM_ROOT}/shared/cpputil
)

target_compile_options(coreproc_plugin_export PRIVATE -fno-function-sections -fno-data-sections)

set_target_properties(coreproc_plugin_export PROPERTIES CXX_STANDARD 23)
