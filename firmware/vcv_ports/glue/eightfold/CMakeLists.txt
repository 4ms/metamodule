cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
	include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(eightfoldMetaModulePlugin 
    VERSION 	0.1 
    DESCRIPTION "eightfold Plugin for MetaModule" 
    LANGUAGES 	C CXX ASM
)

include(modules.cmake)

add_library(eightfoldLibrary OBJECT ${EIGHTFOLD_SOURCE_PATHS}
)

target_include_directories(eightfoldLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../eightfold/src)

target_compile_options(eightfoldLibrary PRIVATE -Wno-double-promotion)

set_property(TARGET eightfoldLibrary PROPERTY CXX_STANDARD 20)

if (BUILD_DYN_PLUGIN)
    target_sources(eightfoldLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/plugin.cpp)

	create_plugin(
		SOURCE_LIB      eightfoldLibrary
		SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/eightfold
		DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins/eightfold
	)
endif()
