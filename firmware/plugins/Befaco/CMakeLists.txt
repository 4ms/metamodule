cmake_minimum_required(VERSION 3.22)
include(../VCV-metamodule-adaptor/plugin.cmake)

project(
    Befaco
    VERSION 0.1
    DESCRIPTION "Befaco Plugin for MetaModule"
    LANGUAGES C CXX 
)

add_library(Befaco STATIC)

target_link_libraries(Befaco PRIVATE mm_vcv_plugin)

set(BEFACODIR ../../vcv_ports/Befaco)

target_sources(Befaco PUBLIC
    plugin.cpp
    ${BEFACODIR}/src/DualAtenuverter.cpp
    ${BEFACODIR}/src/ABC.cpp
    ${BEFACODIR}/src/ADSR.cpp
    ${BEFACODIR}/src/ChoppingKinky.cpp
    ${BEFACODIR}/src/HexmixVCA.cpp
    ${BEFACODIR}/src/Kickall.cpp
    ${BEFACODIR}/src/Mixer.cpp
    ${BEFACODIR}/src/Morphader.cpp
    ${BEFACODIR}/src/MotionMTR.cpp
    ${BEFACODIR}/src/Percall.cpp
    ${BEFACODIR}/src/Rampage.cpp
    ${BEFACODIR}/src/STMix.cpp
    ${BEFACODIR}/src/SamplingModulator.cpp
    ${BEFACODIR}/src/SlewLimiter.cpp
    ${BEFACODIR}/src/StereoStrip.cpp
    ${BEFACODIR}/src/EvenVCO.cpp
    ${BEFACODIR}/src/PonyVCO.cpp
    ${BEFACODIR}/src/SpringReverb.cpp
)

target_include_directories(Befaco PRIVATE
    .
    ${BEFACODIR}/src
)

set_property(TARGET Befaco PROPERTY CXX_STANDARD 20)

target_compile_options(Befaco PRIVATE -Wno-deprecated-enum-float-conversion)

create_plugin("Befaco")
