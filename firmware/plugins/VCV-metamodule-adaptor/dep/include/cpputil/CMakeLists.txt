project(cpputil CXX)

add_library(cpputil)

set_property(TARGET cpputil PROPERTY CXX_STANDARD 20)

target_include_directories(cpputil PUBLIC .)

target_sources(cpputil PRIVATE
    util/math_tables.cc
    util/int_to_str.cc
)

set_property(TARGET cpputil PROPERTY CXX_STANDARD 20)


