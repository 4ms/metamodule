cmake_minimum_required(VERSION 3.22)

project(
  BefacoMetaModulePlugin
  VERSION 0.1
  DESCRIPTION "Befaco Plugin for MetaModule"
  LANGUAGES C CXX ASM
)

# Path to the VCV Rack plugin submodule
set(BEFACO_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Befaco)

add_library(BefacoLibrary STATIC)

target_sources(
  BefacoLibrary
  PRIVATE ${BEFACO_DIR}/src/EvenVCO.cpp
          ${BEFACO_DIR}/src/DualAtenuverter.cpp
          ${BEFACO_DIR}/src/SpringReverb.cpp
          ${BEFACO_DIR}/src/ABC.cpp
          ${BEFACO_DIR}/src/AxBC.cpp
          ${BEFACO_DIR}/src/ADSR.cpp
          ${BEFACO_DIR}/src/Atte.cpp
          ${BEFACO_DIR}/src/ChoppingKinky.cpp
          ${BEFACO_DIR}/src/HexmixVCA.cpp
          ${BEFACO_DIR}/src/Kickall.cpp
          ${BEFACO_DIR}/src/Mixer.cpp
          ${BEFACO_DIR}/src/Mixer2.cpp
          ${BEFACO_DIR}/src/Morphader.cpp
          ${BEFACO_DIR}/src/MotionMTR.cpp
          ${BEFACO_DIR}/src/MuDi.cpp
          ${BEFACO_DIR}/src/Percall.cpp
          ${BEFACO_DIR}/src/PonyVCO.cpp
          ${BEFACO_DIR}/src/Rampage.cpp
          ${BEFACO_DIR}/src/STMix.cpp
          ${BEFACO_DIR}/src/SamplingModulator.cpp
          ${BEFACO_DIR}/src/Slew.cpp
          ${BEFACO_DIR}/src/SlewLimiter.cpp
          ${BEFACO_DIR}/src/StereoStrip.cpp
          ${BEFACO_DIR}/src/Voltio.cpp
          ${BEFACO_DIR}/src/Burst.cpp
          ${BEFACO_DIR}/src/Octaves.cpp
          ${BEFACO_DIR}/src/Muxlicer.cpp
          ${BEFACO_DIR}/src/NoisePlethora.cpp
          ${BEFACO_DIR}/src/Bandit.cpp
          # disabled: MidiThingv2 and Bypass
          ${BEFACO_DIR}/src/noise-plethora/plugins/Banks.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_bitcrusher.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_combine.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_flange.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_freeverb.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_granular.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_multiply.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/effect_wavefolder.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/filter_variable.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/synth_pinknoise.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/synth_pwm.cpp
          ${BEFACO_DIR}/src/noise-plethora/teensy/synth_whitenoise.cpp
)

target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/src .)
target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/../../) # For Befaco SpringReverb to find IR.h file

target_compile_options(
  BefacoLibrary PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
                        -Wno-asm-operand-widths
)

target_compile_definitions(BefacoLibrary PRIVATE METAMODULE)

set_property(TARGET BefacoLibrary PROPERTY CXX_STANDARD 23)
