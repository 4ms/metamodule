cmake_minimum_required (VERSION 3.15 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)

project ("base64_test")

include_directories(doctest)

enable_testing()

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/def_encoding_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/url_encoding_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/traits_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/custom_buffer_test.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})
add_test(NAME ${PROJECT_NAME} COMMAND ./base64_test)

# NOTE: Don't use space inside a generator expression here, because the function prematurely breaks the expression into
# multiple lines. https://cmake.org/pipermail/cmake/2018-April/067422.html
set(SJTEST_GCC_FLAGS -Wall -Wextra -Wpedantic)
set(SJTEST_CLANG_FLAGS -Weverything -Wno-global-constructors -Wno-weak-vtables)
target_compile_options(
  ${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /utf-8> $<$<CXX_COMPILER_ID:GNU>:${SJTEST_GCC_FLAGS}>
                       $<$<CXX_COMPILER_ID:Clang>:${SJTEST_CLANG_FLAGS}>)

message(STATUS "CMAKE_CURRENT_BINARY_DIR=" ${CMAKE_CURRENT_BINARY_DIR})
