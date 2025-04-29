cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(AudibleInstrumentsMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "AudibleInstruments Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

set(AUDIBLE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../AudibleInstruments)

add_library(AudibleInstrumentsLibrary OBJECT
  ${AUDIBLE_DIR}/src/Blinds.cpp
  ${AUDIBLE_DIR}/src/Braids.cpp
  ${AUDIBLE_DIR}/src/Branches.cpp
  ${AUDIBLE_DIR}/src/Clouds.cpp
  ${AUDIBLE_DIR}/src/Elements.cpp
  ${AUDIBLE_DIR}/src/Frames.cpp
  ${AUDIBLE_DIR}/src/Kinks.cpp
  ${AUDIBLE_DIR}/src/Links.cpp
  ${AUDIBLE_DIR}/src/Marbles.cpp
  ${AUDIBLE_DIR}/src/Plaits.cpp
  ${AUDIBLE_DIR}/src/Rings.cpp
  ${AUDIBLE_DIR}/src/Ripples.cpp
  ${AUDIBLE_DIR}/src/Shades.cpp
  ${AUDIBLE_DIR}/src/Shelves.cpp
  ${AUDIBLE_DIR}/src/Stages.cpp
  ${AUDIBLE_DIR}/src/Streams.cpp
  ${AUDIBLE_DIR}/src/Tides.cpp
  ${AUDIBLE_DIR}/src/Tides2.cpp
  ${AUDIBLE_DIR}/src/Veils.cpp
  ${AUDIBLE_DIR}/src/Warps.cpp
)

file(GLOB PLAITS_SOURCES
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/*.cc
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/engine/*.cc
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/speech/*.cc
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/physical_modelling/*.cc
)

target_sources(AudibleInstrumentsLibrary PRIVATE
  ${AUDIBLE_DIR}/eurorack/stmlib/utils/random.cc
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/atan.cc
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/units.cc

  ${AUDIBLE_DIR}/eurorack/braids/analog_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/digital_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/macro_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/resources.cc

  ${PLAITS_SOURCES}
  ${AUDIBLE_DIR}/eurorack/plaits/resources.cc

  ${AUDIBLE_DIR}/eurorack/clouds/dsp/correlator.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/granular_processor.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/mu_law.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/pvoc/frame_transformation.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/pvoc/phase_vocoder.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/pvoc/stft.cc
  ${AUDIBLE_DIR}/eurorack/clouds/resources.cc


  ${AUDIBLE_DIR}/eurorack/elements/dsp/exciter.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/ominous_voice.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/resonator.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/tube.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/multistage_envelope.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/part.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/string.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/voice.cc
  ${AUDIBLE_DIR}/eurorack/elements/resources.cc

  ${AUDIBLE_DIR}/eurorack/rings/dsp/fm_voice.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/part.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/string_synth_part.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/string.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/resonator.cc
  ${AUDIBLE_DIR}/eurorack/rings/resources.cc

  ${AUDIBLE_DIR}/eurorack/tides/generator.cc
  ${AUDIBLE_DIR}/eurorack/tides/resources.cc

  ${AUDIBLE_DIR}/eurorack/tides2/poly_slope_generator.cc
  ${AUDIBLE_DIR}/eurorack/tides2/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/tides2/resources.cc

  ${AUDIBLE_DIR}/eurorack/warps/dsp/modulator.cc
  ${AUDIBLE_DIR}/eurorack/warps/dsp/oscillator.cc
  ${AUDIBLE_DIR}/eurorack/warps/dsp/vocoder.cc
  ${AUDIBLE_DIR}/eurorack/warps/dsp/filter_bank.cc
  ${AUDIBLE_DIR}/eurorack/warps/resources.cc

  ${AUDIBLE_DIR}/eurorack/frames/keyframer.cc
  ${AUDIBLE_DIR}/eurorack/frames/resources.cc
  ${AUDIBLE_DIR}/eurorack/frames/poly_lfo.cc

  ${AUDIBLE_DIR}/eurorack/peaks/processors.cc
  ${AUDIBLE_DIR}/eurorack/peaks/resources.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/bass_drum.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/fm_drum.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/high_hat.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/snare_drum.cc
  ${AUDIBLE_DIR}/eurorack/peaks/modulations/lfo.cc
  ${AUDIBLE_DIR}/eurorack/peaks/modulations/multistage_envelope.cc
  ${AUDIBLE_DIR}/eurorack/peaks/pulse_processor/pulse_shaper.cc
  ${AUDIBLE_DIR}/eurorack/peaks/pulse_processor/pulse_randomizer.cc
  ${AUDIBLE_DIR}/eurorack/peaks/number_station/number_station.cc

  ${AUDIBLE_DIR}/eurorack/stages/segment_generator.cc
  ${AUDIBLE_DIR}/eurorack/stages/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/stages/resources.cc

  ${AUDIBLE_DIR}/eurorack/marbles/random/t_generator.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/x_y_generator.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/output_channel.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/lag_processor.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/quantizer.cc
  ${AUDIBLE_DIR}/eurorack/marbles/ramp/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/marbles/resources.cc

  ${AUDIBLE_DIR}/eurorack/streams/resources.cc
  ${AUDIBLE_DIR}/eurorack/streams/processor.cc
  ${AUDIBLE_DIR}/eurorack/streams/follower.cc
  ${AUDIBLE_DIR}/eurorack/streams/lorenz_generator.cc
  ${AUDIBLE_DIR}/eurorack/streams/envelope.cc
  ${AUDIBLE_DIR}/eurorack/streams/svf.cc
  ${AUDIBLE_DIR}/eurorack/streams/vactrol.cc
  ${AUDIBLE_DIR}/eurorack/streams/compressor.cc

)


target_include_directories(AudibleInstrumentsLibrary PRIVATE 
	${AUDIBLE_DIR}/src 
	${AUDIBLE_DIR}/eurorack
	../../
)

target_compile_options(AudibleInstrumentsLibrary
  PRIVATE
    -Wno-double-promotion
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
    $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:GNU>:-Wno-volatile>>
    $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:Clang>:-Wno-deprecated-volatile>>
    $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:AppleClang>:-Wno-deprecated-volatile>>    
    $<$<COMPILE_LANGUAGE:CXX>:$<$<CXX_COMPILER_ID:GNU>:-Wno-class-memaccess>>
    )

# Fixes for compiler warnings in AudibleInstruments:
set_source_files_properties(
  ${AUDIBLE_DIR}/eurorack/braids/digital_oscillator.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-unused-const-variable;-Wno-unused-but-set-variable"
)

# Fix plaits engines using "virtual" instead of "override"
set_source_files_properties(
  ${AUDIBLE_DIR}/eurorack/plaits/plaits.cc
  ${AUDIBLE_DIR}/src/Plaits.cpp
  PROPERTIES COMPILE_OPTIONS "-Wno-suggest-override"
)


# Fix for stmlib STATIC_ASSERT creating typedefs that aren't used
target_compile_options(AudibleInstrumentsLibrary PRIVATE -Wno-unused-local-typedefs)

set_source_files_properties(
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/units.cc PROPERTIES COMPILE_OPTIONS "-Wno-asm-operand-widths"
)

# Silence warning for synth_string_part.cc (used by Rings.cc) which writes 8B into a 4B space.
# Must be PUBLIC to propagate upwards into linkage of main.elf.
# TODO: fix this somehow, so we don't silence this useful warning in other projects.
target_link_options(AudibleInstrumentsLibrary PUBLIC -Wno-stringop-overflow)

# Define TEST so braids dsp/dsp.h works (since it contains raw Cortex-M4 assembly)
target_compile_definitions(AudibleInstrumentsLibrary PRIVATE TEST METAMODULE)

set_property(TARGET AudibleInstrumentsLibrary PROPERTY CXX_STANDARD 23)

if (BUILD_DYN_PLUGIN)
    target_sources(AudibleInstrumentsLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/plugin.cpp)

    create_plugin(
        SOURCE_LIB      AudibleInstrumentsLibrary
        PLUGIN_NAME     AudibleInstruments
        PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/../../AudibleInstruments/plugin.json
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/AudibleInstruments
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/AudibleInstruments
    )
endif()
