set(BEFACO_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Befaco)

set(BefacoModules
    EvenVCO
    DualAtenuverter
    SpringReverb
    ABC
    ADSR
    ChoppingKinky
    HexmixVCA
    Kickall
    Mixer
    Morphader
    MotionMTR
    Percall
    PonyVCO
    Rampage
    STMix
    SamplingModulator
    SlewLimiter
    StereoStrip
    Voltio
    Burst    
    Octaves
    # disabled:
    # Muxlicer NoisePlethora MidiThingv2
)

# svg paths
list(TRANSFORM BefacoModules PREPEND ${BEFACO_DIR}/res/panels/ OUTPUT_VARIABLE BEFACO_FACEPLATE_SVGS)
list(TRANSFORM BEFACO_FACEPLATE_SVGS APPEND .svg)

# cpp paths
list(TRANSFORM BefacoModules PREPEND ${BEFACO_DIR}/src/ OUTPUT_VARIABLE BEFACO_SOURCE_PATHS)
list(TRANSFORM BEFACO_SOURCE_PATHS APPEND .cpp)
