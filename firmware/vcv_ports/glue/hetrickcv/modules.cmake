set(HETRICKCV_DIR ${CMAKE_CURRENT_LIST_DIR}/../../hetrickcv)

set(hetrickcvModules
    2To4
    ASR
    AnalogToDigital
    BinaryGate
    BinaryNoise
    Bitshift
    Boolean3
    Chaos1Op
    Chaos2Op
    Chaos3Op
    ChaoticAttractors
    ClockedNoise
    Comparator
    Contrast
    Crackle
    DataCompander
    Delta
    DigitalToAnalog
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
    PhasorMixer
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
    Probability
    RandomGates
    Rotator
    Rungler
    Scanner
    VectorMix
    Waveshaper
    XYToPolar
)

# cpp paths
list(TRANSFORM hetrickcvModules PREPEND ${HETRICKCV_DIR}/src/ OUTPUT_VARIABLE HETRICKCV_SOURCE_PATHS)
list(TRANSFORM HETRICKCV_SOURCE_PATHS APPEND .cpp)

# svg paths
list(TRANSFORM hetrickcvModules PREPEND ${HETRICKCV_DIR}/res/ OUTPUT_VARIABLE HETRICKCV_FACEPLATE_SVGS)
list(TRANSFORM HETRICKCV_FACEPLATE_SVGS APPEND .svg)
