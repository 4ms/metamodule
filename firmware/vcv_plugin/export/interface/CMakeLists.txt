cmake_minimum_required(VERSION 3.24)
project(VCV-Plugin-Interface)

#######################

# TODO: This needs to be removed eventually
set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../..)

if (NOT TARGET metamodule::rack-interface)
  add_subdirectory(${MM_ROOT}/firmware/metamodule-plugin-sdk/metamodule-rack-interface metamodule-rack-interface)
endif()

if (NOT TARGET metamodule::core-interface)
  add_subdirectory(${MM_ROOT}/firmware/metamodule-plugin-sdk/metamodule-core-interface metamodule-core-interface)
endif()

#######################

# Create interface library for use by vcv_ports (built-in vcv modules)
add_library(vcv_plugin_interface INTERFACE)
add_library(metamodule::vcv-plugin-interface ALIAS vcv_plugin_interface)

target_link_libraries(vcv_plugin_interface
  INTERFACE
    metamodule::rack-interface
    metamodule::core-interface
)

