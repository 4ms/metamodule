set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../..)
set(4MS_DIR ${MM_ROOT}/shared/CoreModules/4ms/core)

set(4msModules
    ADEnv
    Atvert2
    BPF
    BuffMult
    CLKD
    CLKM
    Comp
    ComplexEG
    DEV
    DLD
    Detune
    Djembe
    Drum
    ENVVCA
    EnOsc
    FM
    Fade
    Follow
    Freeverb
    GRev
    Gate32
    Gate8
    Gate
    HPF
    InfOsc
    KPLS
    L4
    LPF
    LPG
    MNMX
    Mixer4
    MultiLFO
    Noise
    Octave
    PEG
    PI
    Pan
    PitchShift
    Prob8
    QCD
    QPLFO
    Quant
    RCD
    SCM
    SH
    SHEV
    SISM
    STS
    Seq4
    Seq8
    Sequant
    Slew
    Source
    StMix
    Switch14
    Switch41
    Tapo
    VCAM
    Verb
)

# svg paths
list(TRANSFORM 4msModules PREPEND ${MM_ROOT}/vcv/res/modules/ OUTPUT_VARIABLE 4MS_FACEPLATE_SVGS)
list(TRANSFORM 4MS_FACEPLATE_SVGS APPEND _artwork.svg)

# src paths
list(TRANSFORM 4msModules PREPEND ${4MS_DIR}/ OUTPUT_VARIABLE 4MS_SOURCE_PATHS)
list(TRANSFORM 4MS_SOURCE_PATHS APPEND Core.cc)
