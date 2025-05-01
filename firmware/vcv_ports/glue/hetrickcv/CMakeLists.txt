cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(hetrickcvMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "hetrickcv Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

set(HETRICKCV_DIR ${CMAKE_CURRENT_LIST_DIR}/../../hetrickcv)

set(HETRICKCV_SOURCE_PATHS
    ${HETRICKCV_DIR}/src/2To4.cpp
    ${HETRICKCV_DIR}/src/ASR.cpp
    ${HETRICKCV_DIR}/src/AnalogToDigital.cpp
    ${HETRICKCV_DIR}/src/BinaryCounter.cpp
    ${HETRICKCV_DIR}/src/BinaryGate.cpp
    ${HETRICKCV_DIR}/src/BinaryNoise.cpp
    ${HETRICKCV_DIR}/src/Bitshift.cpp
    ${HETRICKCV_DIR}/src/Boolean3.cpp
    ${HETRICKCV_DIR}/src/Chaos1Op.cpp
    ${HETRICKCV_DIR}/src/Chaos2Op.cpp
    ${HETRICKCV_DIR}/src/Chaos3Op.cpp
    ${HETRICKCV_DIR}/src/ChaoticAttractors.cpp
    ${HETRICKCV_DIR}/src/ClockedNoise.cpp
    ${HETRICKCV_DIR}/src/ClockToPhasor.cpp
    ${HETRICKCV_DIR}/src/Comparator.cpp
    ${HETRICKCV_DIR}/src/Contrast.cpp
    ${HETRICKCV_DIR}/src/Crackle.cpp
    ${HETRICKCV_DIR}/src/DataCompander.cpp
    ${HETRICKCV_DIR}/src/Delta.cpp
    ${HETRICKCV_DIR}/src/DigitalToAnalog.cpp
    ${HETRICKCV_DIR}/src/Dust.cpp
    ${HETRICKCV_DIR}/src/Exponent.cpp
    ${HETRICKCV_DIR}/src/FBSineChaos.cpp
    ${HETRICKCV_DIR}/src/FlipFlop.cpp
    ${HETRICKCV_DIR}/src/FlipPan.cpp
    ${HETRICKCV_DIR}/src/GateDelay.cpp
    ${HETRICKCV_DIR}/src/GateJunction.cpp
    ${HETRICKCV_DIR}/src/GateJunctionExp.cpp
    ${HETRICKCV_DIR}/src/Gingerbread.cpp
    ${HETRICKCV_DIR}/src/LogicCombine.cpp
    ${HETRICKCV_DIR}/src/MidSide.cpp
    ${HETRICKCV_DIR}/src/MinMax.cpp
    ${HETRICKCV_DIR}/src/Normals.cpp
    ${HETRICKCV_DIR}/src/PhaseDrivenSequencer.cpp
    ${HETRICKCV_DIR}/src/PhaseDrivenSequencer32.cpp
    ${HETRICKCV_DIR}/src/PhasorAnalyzer.cpp
    ${HETRICKCV_DIR}/src/PhasorBurstGen.cpp
    ${HETRICKCV_DIR}/src/PhasorDivMult.cpp
    ${HETRICKCV_DIR}/src/PhasorEuclidean.cpp
    ${HETRICKCV_DIR}/src/PhasorFreezer.cpp
    ${HETRICKCV_DIR}/src/PhasorGates.cpp
    ${HETRICKCV_DIR}/src/PhasorGates32.cpp
    ${HETRICKCV_DIR}/src/PhasorGates64.cpp
    ${HETRICKCV_DIR}/src/PhasorGen.cpp
    ${HETRICKCV_DIR}/src/PhasorGeometry.cpp
    ${HETRICKCV_DIR}/src/PhasorHumanizer.cpp
    ${HETRICKCV_DIR}/src/PhasorMixer.cpp
    ${HETRICKCV_DIR}/src/PhasorOctature.cpp
    ${HETRICKCV_DIR}/src/PhasorProbability.cpp
    ${HETRICKCV_DIR}/src/PhasorQuadrature.cpp
    ${HETRICKCV_DIR}/src/PhasorRandom.cpp
    ${HETRICKCV_DIR}/src/PhasorRanger.cpp
    ${HETRICKCV_DIR}/src/PhasorReset.cpp
    ${HETRICKCV_DIR}/src/PhasorRhythmGroup.cpp
    ${HETRICKCV_DIR}/src/PhasorShape.cpp
    ${HETRICKCV_DIR}/src/PhasorShift.cpp
    ${HETRICKCV_DIR}/src/PhasorSplitter.cpp
    ${HETRICKCV_DIR}/src/PhasorStutter.cpp
    ${HETRICKCV_DIR}/src/PhasorSubstepShape.cpp
    ${HETRICKCV_DIR}/src/PhasorSwing.cpp
    ${HETRICKCV_DIR}/src/PhasorTimetable.cpp
    ${HETRICKCV_DIR}/src/PhasorToClock.cpp
    ${HETRICKCV_DIR}/src/PhasorToLFO.cpp
    ${HETRICKCV_DIR}/src/PhasorToRandom.cpp
    ${HETRICKCV_DIR}/src/PhasorToWaveforms.cpp
    ${HETRICKCV_DIR}/src/PolymetricPhasors.cpp
    ${HETRICKCV_DIR}/src/Probability.cpp
    ${HETRICKCV_DIR}/src/RandomGates.cpp
    ${HETRICKCV_DIR}/src/Rotator.cpp
    ${HETRICKCV_DIR}/src/Rungler.cpp
    ${HETRICKCV_DIR}/src/Scanner.cpp
    ${HETRICKCV_DIR}/src/TrigShaper.cpp
    ${HETRICKCV_DIR}/src/VectorMix.cpp
    ${HETRICKCV_DIR}/src/Waveshaper.cpp
    ${HETRICKCV_DIR}/src/XYToPolar.cpp
)

file(
  GLOB
  DSP_SOURCES
  ${HETRICKCV_DIR}/src/DSP/*.cpp
  ${HETRICKCV_DIR}/src/DSP/Phasors/*.cpp
)

set(EXTRA_SOURCES ${HETRICKCV_DIR}/src/HetrickUtilities.cpp)

set(GAMMA_SOURCES
    ${HETRICKCV_DIR}/Gamma/src/arr.cpp
    ${HETRICKCV_DIR}/Gamma/src/DFT.cpp
    ${HETRICKCV_DIR}/Gamma/src/Domain.cpp
    ${HETRICKCV_DIR}/Gamma/src/FFT_fftpack.cpp
    ${HETRICKCV_DIR}/Gamma/src/fftpack++1.cpp
    ${HETRICKCV_DIR}/Gamma/src/fftpack++2.cpp
    ${HETRICKCV_DIR}/Gamma/src/scl.cpp
)

add_library(
  hetrickcvLibrary OBJECT
  ${HETRICKCV_SOURCE_PATHS}
  ${DSP_SOURCES}
  ${EXTRA_SOURCES}
  ${GAMMA_SOURCES}
)

target_include_directories(hetrickcvLibrary PRIVATE ${HETRICKCV_DIR}/Gamma ${HETRICKCV_DIR}/src)

set_property(TARGET hetrickcvLibrary PROPERTY CXX_STANDARD 23)

set_source_files_properties(${HETRICKCV_DIR}/src/Rungler.cpp PROPERTIES COMPILE_OPTIONS "-Wno-sign-compare")

target_compile_options(
  hetrickcvLibrary
  PRIVATE 
          # Fixes for warnings with Gamma:
          -Wno-misleading-indentation
          -Wno-unused-but-set-variable
          -Wno-unused-function
          # Fixes for warnings with DSP and main source:
          -Wno-unused-variable
)

if (BUILD_DYN_PLUGIN)
    target_sources(hetrickcvLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/HetrickCV.cpp)

    create_plugin(
        SOURCE_LIB      hetrickcvLibrary
        PLUGIN_NAME     hetrickcv
        PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/../../hetrickcv/plugin.json
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/hetrickcv
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/hetrickcv
    )
endif()
