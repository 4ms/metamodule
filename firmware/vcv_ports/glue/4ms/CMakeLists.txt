include(modules.cmake)

add_library(
  4msLibrary OBJECT
  ${4MS_SOURCE_PATHS}
)

set_property(TARGET 4msLibrary PROPERTY CXX_STANDARD 20)

target_link_libraries(4msLibrary PRIVATE cpputil)

target_include_directories(
  4msLibrary
  PUBLIC ${MM_ROOT}/shared
         ${MM_ROOT}/shared/CoreModules/4ms
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

# Axoloti ports
target_sources(
	4msLibrary
	PRIVATE
    ${MM_ROOT}/shared/CoreModules/4ms/core/axoloti-wrapper/axoloti_math.cpp
)
