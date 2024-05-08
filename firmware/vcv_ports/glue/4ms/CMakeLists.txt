include(modules.cmake)

####################

# TODO: This is actually not 4ms specific but relevant for all modules that use SmartCoreProcessor

if (NOT TARGET ryml)
  add_subdirectory(${MM_ROOT}/shared/patch_convert/ryml/rapidyaml rapidyaml)
endif()

####################

add_library(
  4msLibrary OBJECT
  ${4MS_SOURCE_PATHS}
)

set_property(TARGET 4msLibrary PROPERTY CXX_STANDARD 20)

if (NOT DEFINED alpaca)
  add_subdirectory(${MM_ROOT}/shared/CoreModules/4ms/core/alpaca alpaca)
  target_compile_definitions(alpaca INTERFACE ALPACA_NO_PREFETCH)
endif()

target_link_libraries(4msLibrary PRIVATE cpputil ryml alpaca::alpaca)

target_include_directories(
  4msLibrary
  PUBLIC ${MM_ROOT}/shared
         ${MM_ROOT}/shared/CoreModules/4ms
		 ${MM_ROOT}/shared/patch_convert/ryml #For ryml_serial
)

# Ensemble Oscillator
target_sources(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
)

# Tapographic Delay
target_compile_definitions(
  4msLibrary
  PRIVATE
    SAMPLE_RATE=48000
    TEST
)

target_include_directories(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/
)

target_sources(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/multitap_delay.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/resources.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/tap_allocator.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/control.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/ui.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/stmlib/utils/random.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/tapo/stmlib/dsp/units.cc
)

# QPLFO
target_sources(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/qplfo/qplfo.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/qplfo/qplfo_mocks.cc
)

#MPEG
# MiniPEG
target_sources(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/main.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/trigout.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/analog_conditioning.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/env_update.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/envelope_calcs.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/flash_user.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/params.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/pingable_env.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/dig_inouts.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/timers.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/calibration.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/env_transition.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/leds.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/shareddrv/debounced_digins.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/shareddrv/dac.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/pwm.cc
)
target_include_directories(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg
    ${MM_ROOT}/shared/CoreModules/4ms/core/mpeg/mocks
)

# DLD
target_sources(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/looping-delay/src/calibration_storage.cc
)

target_include_directories(
  4msLibrary
  PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/looping-delay/src
)

# Axoloti ports
target_sources(
	4msLibrary
	PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/axoloti-wrapper/axoloti_math.cpp
)
