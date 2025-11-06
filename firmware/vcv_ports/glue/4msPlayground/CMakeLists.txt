 cmake_minimum_required(VERSION 3.19)

if (BUILD_DYN_PLUGIN)

if(NOT "${METAMODULE_SDK_DIR}" STREQUAL "")
	message("METAMODULE_SDK_DIR set by CMake variable ${METAMODULE_SDK_DIR}")
elseif (DEFINED ENV{METAMODULE_SDK_DIR})
    set(METAMODULE_SDK_DIR "$ENV{METAMODULE_SDK_DIR}")
	message("METAMODULE_SDK_DIR set by environment variable ${METAMODULE_SDK_DIR}")
else()
    set(METAMODULE_SDK_DIR "${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk")
	message("METAMODULE_SDK_DIR set to default: ${METAMODULE_SDK_DIR}")
endif()
include(${METAMODULE_SDK_DIR}/plugin.cmake)

endif()


project(4ms-Playground VERSION 0.1 DESCRIPTION "4ms-Playground for MetaModule" LANGUAGES C CXX ASM)

add_library(4msPlaygroundLibrary STATIC)

# Add sources from the Rack source repo
# set(SOURCE_DIR .)
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../../../mm-plugins/playground)

target_sources(4msPlaygroundLibrary PRIVATE
    ${SOURCE_DIR}/src/pinwheel.cpp              
    ${SOURCE_DIR}/src/chimes.cpp               
    # ${SOURCE_DIR}/src/GraphicsLimit.cpp       
    # ${SOURCE_DIR}/src/Screen.cpp             
    ${SOURCE_DIR}/src/SideScroller.cpp      
    # ${SOURCE_DIR}/src/plugin.cpp
    # ${SOURCE_DIR}/src/plugin.hpp
) 

# Add includes and compile options for source repo
target_include_directories(4msPlaygroundLibrary PRIVATE ${SOURCE_DIR}/src)

# Call this to link and create the plugin file
if (BUILD_DYN_PLUGIN)
create_plugin(
    SOURCE_LIB      4msPlaygroundLibrary                                          # The cmake target name (defined in add_target)
    PLUGIN_NAME     4ms-Playground                                          # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/plugin.json              # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                  # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins   # Path to where you want the plugin file output
)
endif()
