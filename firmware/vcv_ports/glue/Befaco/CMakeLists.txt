set(BEFACO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../Befaco)

add_library(
  BefacoModules OBJECT
  ${BEFACO_DIR}/src/EvenVCO.cpp
  ${BEFACO_DIR}/src/DualAtenuverter.cpp
  ${BEFACO_DIR}/src/SpringReverb.cpp
  ${BEFACO_DIR}/src/ABC.cpp
  ${BEFACO_DIR}/src/ADSR.cpp
  ${BEFACO_DIR}/src/ChoppingKinky.cpp
  ${BEFACO_DIR}/src/HexmixVCA.cpp
  ${BEFACO_DIR}/src/Kickall.cpp
  ${BEFACO_DIR}/src/Mixer.cpp
  ${BEFACO_DIR}/src/Morphader.cpp
  ${BEFACO_DIR}/src/MotionMTR.cpp
  ${BEFACO_DIR}/src/Percall.cpp
  ${BEFACO_DIR}/src/PonyVCO.cpp
  ${BEFACO_DIR}/src/Rampage.cpp
  ${BEFACO_DIR}/src/STMix.cpp
  ${BEFACO_DIR}/src/SamplingModulator.cpp
  ${BEFACO_DIR}/src/SlewLimiter.cpp
  ${BEFACO_DIR}/src/StereoStrip.cpp
  # ${BEFACO_DIR}/src/Muxlicer.cpp ${BEFACO_DIR}/src/NoisePlethora.cpp
)

target_include_directories(BefacoModules PRIVATE ${BEFACO_DIR}/src ${PROJECT_SOURCE_DIR}/src/VCV_adaptor/pffft)

target_compile_options(BefacoModules PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)
