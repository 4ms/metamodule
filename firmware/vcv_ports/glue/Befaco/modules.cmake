set(BEFACO_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Befaco)

set(BefacoModules
    EvenVCO
    DualAtenuverter
    SpringReverb
    ABC
    AxBC
    ADSR
    Atte
    ChoppingKinky
    HexmixVCA
    Kickall
    Mixer
    Mixer2
    Morphader
    MotionMTR
    MuDi
    Percall
    PonyVCO
    Rampage
    STMix
    SamplingModulator
    Slew
    SlewLimiter
    StereoStrip
    Voltio
    Burst    
    Octaves    
    Muxlicer 
    NoisePlethora
    Bandit    
    # disabled:
    # MidiThingv2
    # Bypass (for now, due to odd UI interactions)
)

# svg paths
list(TRANSFORM BefacoModules PREPEND ${BEFACO_DIR}/res/panels/ OUTPUT_VARIABLE BEFACO_FACEPLATE_SVGS)
list(TRANSFORM BEFACO_FACEPLATE_SVGS APPEND .svg)

# cpp paths
list(TRANSFORM BefacoModules PREPEND ${BEFACO_DIR}/src/ OUTPUT_VARIABLE BEFACO_SOURCE_PATHS)
list(TRANSFORM BEFACO_SOURCE_PATHS APPEND .cpp)
