cmake_minimum_required(VERSION 3.22)

project(
  ListenCloselyMetaModulePlugin
  VERSION 0.1
  DESCRIPTION "Listen Closely for MetaModule"
  LANGUAGES C CXX ASM
)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../listenclosely)

add_library(ListenCloselyLibrary OBJECT ${SOURCE_DIR}/ListenClosely.cpp)

target_include_directories(ListenCloselyLibrary PRIVATE ${SOURCE_DIR})

# target_compile_options(ListenCloselyLibrary PRIVATE -Wno-double-promotion)

set_property(TARGET ListenCloselyLibrary PROPERTY CXX_STANDARD 23)
