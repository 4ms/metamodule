include(modules.cmake)

####################

# TODO: This is actually not 4ms specific but relevant for all modules that use SmartCoreProcessor

if (NOT TARGET ryml)
  add_subdirectory(${MM_ROOT}/shared/patch_convert/ryml/rapidyaml rapidyaml)
endif()

####################

add_library(4msLibrary OBJECT
  ${4MS_SOURCE_PATHS}
)

set_property(TARGET 4msLibrary PROPERTY CXX_STANDARD 23)

if (NOT DEFINED alpaca)
  add_subdirectory(${MM_ROOT}/shared/CoreModules/4ms/core/alpaca alpaca)
  target_compile_definitions(alpaca INTERFACE ALPACA_NO_PREFETCH)
endif()

target_link_libraries(4msLibrary PRIVATE cpputil ryml alpaca::alpaca)

target_include_directories(4msLibrary PUBLIC 
    ${MM_ROOT}/shared
    ${MM_ROOT}/shared/CoreModules/4ms
    ${MM_ROOT}/shared/patch_convert/ryml #For ryml_serial
)

target_include_directories(4msLibrary
    PUBLIC ${MM_ROOT}/firmware/lib/fatfs/source 
           ${MM_ROOT}/firmware/src/fs/fatfs
)

# Ensemble Oscillator
target_sources(4msLibrary PRIVATE 
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
)

# Tapographic Delay
target_compile_definitions(4msLibrary PRIVATE 
    SAMPLE_RATE=48000
)

target_include_directories(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/)

target_sources(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/multitap_delay.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/resources.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/tap_allocator.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/control.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/ui.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/stmlib/utils/random.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/stmlib/dsp/units.cc
)

# QPLFO
target_sources(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/qplfo/qplfo.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/qplfo/qplfo_mocks.cc
)

#MPEG
# MiniPEG
target_sources(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/peg_base.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/trigout.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/analog_conditioning.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/env_update.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/envelope_calcs.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/flash_user.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/params.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/pingable_env.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/dig_inouts.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/timers.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/calibration.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/env_transition.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/leds.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/shareddrv/debounced_digins.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/shareddrv/dac.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/pwm.cc

    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/envelope_calcs.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg/envelope_calcs.cc
)

target_include_directories(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/
    ${MM_ROOT}/shared/CoreModules/4ms/core/peg-common/mocks
)

# DLD
target_sources(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/looping-delay/src/calibration_storage.cc
)

target_include_directories(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/looping-delay/src
)

# Sampler
target_sources(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/mocks/calibration_storage.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/mocks/time.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/bank.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/sample_file.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/sts_filesystem.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/sts_sampleindex.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/sample_header.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/str_util.c
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/bank.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/bank_util.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src/wavefmt.cc
)

target_include_directories(4msLibrary PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/src
    ${MM_ROOT}/shared/CoreModules/4ms/core/sampler/mocks
)
target_compile_definitions(4msLibrary PRIVATE 
    METAMODULE
)

# Axoloti ports
# target_sources(4msLibrary PRIVATE
#     ${MM_ROOT}/shared/CoreModules/4ms/core/axoloti-wrapper/axoloti_math.cpp
# )
