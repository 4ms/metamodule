set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../..)
set(4MS_DIR ${MM_ROOT}/shared/CoreModules/4ms/core)

set(4msModules
    # ADEnv
    Atvert2
    BPF
    CLKD
    CLKM
    ComplexEG
    DEV
    DLD
    Detune
    Djembe
    Drum
    ENVVCA
    EnOsc
    FM
    Follow
    Freeverb
    Gate
    HPF
    KPLS
    L4
    # LPF
    # LPG
    MNMX
    MPEG
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
    # Quant
    RCD
    SCM
    SH
    SHEV
    SISM
    STS
    Seq8
    Slew
    # Source
    StMix
    Switch14
    Switch41
    Tapo
    VCAM
    Verb
)

# Info svgs (used to generate info.hh files and VCV svgs)
list(TRANSFORM 4msModules PREPEND ${MM_ROOT}/shared/CoreModules/4ms/svg/ OUTPUT_VARIABLE 4MS_INFO_SVGS)
list(TRANSFORM 4MS_INFO_SVGS APPEND _info.svg)

# VCV svgs (used in VCV and also to create LVGL images)
list(TRANSFORM 4msModules PREPEND ${MM_ROOT}/vcv/res/modules/ OUTPUT_VARIABLE 4MS_FACEPLATE_SVGS)
list(TRANSFORM 4MS_FACEPLATE_SVGS APPEND _artwork.svg)

# src paths
list(TRANSFORM 4msModules PREPEND ${4MS_DIR}/ OUTPUT_VARIABLE 4MS_SOURCE_PATHS)
list(TRANSFORM 4MS_SOURCE_PATHS APPEND Core.cc)
