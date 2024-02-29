project(Modules)

add_library(modules INTERFACE)

# TODO: this should be removed and includes adapted
target_include_directories(modules INTERFACE .)

target_include_directories(modules INTERFACE CoreModules/elements)
target_include_directories(modules INTERFACE CoreModules)