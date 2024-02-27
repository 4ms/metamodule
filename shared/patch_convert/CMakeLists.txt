project(PatchConvert)

add_library(patch_convert)

set_property(TARGET patch_convert PROPERTY CXX_STANDARD 20)

add_subdirectory(ryml/rapidyaml)

target_sources(patch_convert PRIVATE
    ryml/ryml_serial.cc
    yaml_to_patch.cc 
    patch_to_yaml.cc
)

target_include_directories(patch_convert PUBLIC
    ../patch
    ../CoreModules)

target_link_libraries(patch_convert PUBLIC ryml cpputil)