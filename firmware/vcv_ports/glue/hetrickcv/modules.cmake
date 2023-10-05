set(HETRICKCV_DIR ${CMAKE_CURRENT_LIST_DIR}/../../hetrickcv)

set(hetrickcvModules
    ASR
    AToD
    BinaryGate
    BinaryNoise
    Bitshift
    Boolean3
    Chaos1Op
    Chaos2Op
    Chaos3Op
    ChaoticAttractors
    ClockedNoise
    Contrast
    Crackle
    # skip: DataCompander, Delta
    DToA
    Dust
    Exponent
    FBSineChaos
    FlipFlop
    FlipPan
    GateDelay
    GateJunction
    GateJunctionExp
    Gingerbread
    LogicCombine
    MidSide
    MinMax
    PhaseDrivenSequencer
    PhaseDrivenSequencer32
    PhasorAnalyzer
    PhasorBurstGen
    PhasorDivMult
    PhasorEuclidean
    PhasorGates
    PhasorGates32
    PhasorGates64
    PhasorGen
    PhasorGeometry
    PhasorHumanizer
    PhasorOctature
    PhasorQuadrature
    PhasorRandom
    PhasorRanger
    PhasorReset
    PhasorRhythmGroup
    PhasorShape
    PhasorShift
    PhasorStutter
    PhasorSubstepShape
    PhasorSwing
    PhasorTimetable
    PhasorToClock
    PhasorToLFO
    PhasorToWaveforms
    XYToPolar
    Probability
    Scanner
    TwoToFour
    VectorMix
    Waveshape
)

# TODO: use this. List is in pairs (SVG name, VCV slug)
set(hetrickcvAltNames
    AToD
    AnalogToDigital
    DToA
    DigitalToAnalog
    2To4
    TwoToFour
    Waveshaper
    Waveshape
)

include(${CMAKE_CURRENT_LIST_DIR}/../filter.cmake)
limit_modules_built(hetrickcvModules)

# cpp paths
list(TRANSFORM hetrickcvModules PREPEND ${HETRICKCV_DIR}/src/ OUTPUT_VARIABLE HETRICKCV_SOURCE_PATHS)
list(TRANSFORM HETRICKCV_SOURCE_PATHS APPEND .cpp)

# svg paths
list(TRANSFORM hetrickcvModules PREPEND ${HETRICKCV_DIR}/res/ OUTPUT_VARIABLE HETRICKCV_FACEPLATE_SVGS)
list(TRANSFORM HETRICKCV_FACEPLATE_SVGS APPEND .svg)
