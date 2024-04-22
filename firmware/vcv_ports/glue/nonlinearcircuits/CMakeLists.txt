cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
	include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(nonlinearcircuitsMetaModulePlugin 
    VERSION 	0.1 
    DESCRIPTION "nonlinearcircuits Plugin for MetaModule" 
    LANGUAGES 	C CXX ASM
)

include(modules.cmake)

set(EXTRA_SOURCES ${NONLINEARCIRCUITS_DIR}/src/NLCShared.cpp)

add_library(
  nonlinearcircuitsLibrary OBJECT
  ${NONLINEARCIRCUITS_SOURCE_PATHS}
  ${EXTRA_SOURCES}
)

target_include_directories(nonlinearcircuitsLibrary PRIVATE ${NONLINEARCIRCUITS_DIR}/src)

set_property(TARGET nonlinearcircuitsLibrary PROPERTY CXX_STANDARD 20)

target_compile_options(
    nonlinearcircuitsLibrary
  PRIVATE -fvisibility=hidden
          $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>
          -Wno-double-promotion
)

if (BUILD_DYN_PLUGIN)
	create_plugin(
		SOURCE_LIB      nonlinearcircuitsLibrary
		SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/nonlinearcircuits
		DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins/nonlinearcircuits
	)
endif()
