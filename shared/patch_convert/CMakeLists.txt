project(PatchConvert)

add_library(patch_convert)

set_property(TARGET patch_convert PROPERTY CXX_STANDARD 20)

if (NOT TARGET ryml)
    add_subdirectory(ryml/rapidyaml)
endif()

if (NOT TARGET modules)
    add_subdirectory(../modules modules)
endif()

target_sources(patch_convert PRIVATE
    ryml/ryml_serial.cc
    yaml_to_patch.cc 
    patch_to_yaml.cc
)

target_include_directories(patch_convert PUBLIC
    ../patch)

target_link_libraries(patch_convert PUBLIC ryml cpputil modules)