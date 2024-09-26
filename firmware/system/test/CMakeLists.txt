cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE "Debug")

project(
  AllocWatchTest
  VERSION 0.10
  DESCRIPTION "Test project for allocation watcher"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test)

target_sources(test PRIVATE
	alloc_watch_test.cc
	../new.cc
)

add_subdirectory(../../lib/cpputil ${CMAKE_CURRENT_BINARY_DIR}/cpputil)

target_link_libraries(test PRIVATE cpputil)

target_compile_definitions(test PRIVATE CPU_TEST_ALL_MODULES)
