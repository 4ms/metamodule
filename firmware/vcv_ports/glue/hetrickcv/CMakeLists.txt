set(HETRICKCV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../hetrickcv)

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
  HetrickcvModules OBJECT
  ${HETRICKCV_DIR}/src/ASR.cpp
  ${HETRICKCV_DIR}/src/AToD.cpp
  ${HETRICKCV_DIR}/src/BinaryGate.cpp
  ${HETRICKCV_DIR}/src/BinaryNoise.cpp
  ${HETRICKCV_DIR}/src/Bitshift.cpp
  ${HETRICKCV_DIR}/src/Boolean3.cpp
  ${HETRICKCV_DIR}/src/Chaos1Op.cpp
  ${HETRICKCV_DIR}/src/Chaos2Op.cpp
  ${HETRICKCV_DIR}/src/Chaos3Op.cpp
  ${HETRICKCV_DIR}/src/ChaoticAttractors.cpp
  ${HETRICKCV_DIR}/src/ClockedNoise.cpp
  ${HETRICKCV_DIR}/src/Comparator.cpp
  ${HETRICKCV_DIR}/src/Contrast.cpp
  ${HETRICKCV_DIR}/src/Crackle.cpp
  ${HETRICKCV_DIR}/src/DToA.cpp
  # ${HETRICKCV_DIR}/src/DataCompander.cpp
  ${HETRICKCV_DIR}/src/Delta.cpp
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
  ${HETRICKCV_DIR}/src/PhaseDrivenSequencer.cpp
  ${HETRICKCV_DIR}/src/PhaseDrivenSequencer32.cpp
  ${HETRICKCV_DIR}/src/PhasorAnalyzer.cpp
  ${HETRICKCV_DIR}/src/PhasorBurstGen.cpp
  ${HETRICKCV_DIR}/src/PhasorDivMult.cpp
  ${HETRICKCV_DIR}/src/PhasorEuclidean.cpp
  ${HETRICKCV_DIR}/src/PhasorGates.cpp
  ${HETRICKCV_DIR}/src/PhasorGates32.cpp
  ${HETRICKCV_DIR}/src/PhasorGates64.cpp
  ${HETRICKCV_DIR}/src/PhasorGen.cpp
  ${HETRICKCV_DIR}/src/PhasorGeometry.cpp
  ${HETRICKCV_DIR}/src/PhasorHumanizer.cpp
  ${HETRICKCV_DIR}/src/PhasorOctature.cpp
  ${HETRICKCV_DIR}/src/PhasorQuadrature.cpp
  ${HETRICKCV_DIR}/src/PhasorRandom.cpp
  ${HETRICKCV_DIR}/src/PhasorRanger.cpp
  ${HETRICKCV_DIR}/src/PhasorReset.cpp
  ${HETRICKCV_DIR}/src/PhasorRhythmGroup.cpp
  ${HETRICKCV_DIR}/src/PhasorShape.cpp
  ${HETRICKCV_DIR}/src/PhasorShift.cpp
  ${HETRICKCV_DIR}/src/PhasorStutter.cpp
  ${HETRICKCV_DIR}/src/PhasorSubstepShape.cpp
  ${HETRICKCV_DIR}/src/PhasorSwing.cpp
  ${HETRICKCV_DIR}/src/PhasorTimetable.cpp
  ${HETRICKCV_DIR}/src/PhasorToClock.cpp
  ${HETRICKCV_DIR}/src/PhasorToLFO.cpp
  ${HETRICKCV_DIR}/src/PhasorToWaveforms.cpp
  ${HETRICKCV_DIR}/src/Polar.cpp
  ${HETRICKCV_DIR}/src/Probability.cpp
  ${HETRICKCV_DIR}/src/RandomGates.cpp
  ${HETRICKCV_DIR}/src/Rotator.cpp
  ${HETRICKCV_DIR}/src/Rungler.cpp
  ${HETRICKCV_DIR}/src/Scanner.cpp
  ${HETRICKCV_DIR}/src/TwoToFour.cpp
  ${HETRICKCV_DIR}/src/VectorMix.cpp
  ${HETRICKCV_DIR}/src/Waveshape.cpp
  ${DSP_SOURCES}
  ${EXTRA_SOURCES}
  ${GAMMA_SOURCES}
)

target_include_directories(HetrickcvModules PRIVATE ${HETRICKCV_DIR}/src ${HETRICKCV_DIR}/Gamma)

target_compile_options(HetrickcvModules PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)
