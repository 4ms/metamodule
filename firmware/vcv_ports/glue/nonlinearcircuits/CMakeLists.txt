cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(nonlinearcircuitsMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "nonlinearcircuits Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

set(NONLINEARCIRCUITS_DIR ${CMAKE_CURRENT_LIST_DIR}/../../nonlinearcircuits)

add_library(
    nonlinearcircuitsLibrary OBJECT

    ${NONLINEARCIRCUITS_DIR}/src/4Seq.cpp
    ${NONLINEARCIRCUITS_DIR}/src/8BitCipher.cpp
    ${NONLINEARCIRCUITS_DIR}/src/BOOLs.cpp
    ${NONLINEARCIRCUITS_DIR}/src/DivideConquer.cpp
    ${NONLINEARCIRCUITS_DIR}/src/DivineCMOS.cpp
    ${NONLINEARCIRCUITS_DIR}/src/DoubleNeuron.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Genie.cpp
    ${NONLINEARCIRCUITS_DIR}/src/LetsSplosh.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Neuron.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Numberwang.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Router.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Segue.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SlothApathy.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SlothInertia.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SlothTorpor.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SquidAxon.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Splish.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Statues.cpp
    ${NONLINEARCIRCUITS_DIR}/src/TripleSloth.cpp

    ${NONLINEARCIRCUITS_DIR}/src/NLCShared.cpp
)

target_include_directories(nonlinearcircuitsLibrary PRIVATE ${NONLINEARCIRCUITS_DIR}/src)

set_property(TARGET nonlinearcircuitsLibrary PROPERTY CXX_STANDARD 23)

target_compile_options(
    nonlinearcircuitsLibrary
    PRIVATE
          -Wno-double-promotion
)

if (BUILD_DYN_PLUGIN)
    target_sources(nonlinearcircuitsLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/NLC.cpp)

    create_plugin(
        SOURCE_LIB      nonlinearcircuitsLibrary
        PLUGIN_NAME     nonlinearcircuits
        PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/../../nonlinearcircuits/plugin.json
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/nonlinearcircuits
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/nonlinearcircuits
    )
endif()
