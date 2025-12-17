cmake_minimum_required(VERSION 3.24)
project(CoreProc-Plugin)

add_library(coreproc_plugin_export STATIC)

target_sources(
  coreproc_plugin_export
  PRIVATE async_thread.cc
          audio/settings.cc
          dsp/block_resampler.cc
          dsp/stream_resampler.cc
          gui/notification.cc
          patch/patch.cc
          wav/wav_file_stream.cc
          wav/dr_wav.c
          midi_message.cc
)

if(NOT DEFINED METAMODULE_HEADLESS)
  target_sources(coreproc_plugin_export PRIVATE graphics/waveform_display.cc)
else()
  target_sources(coreproc_plugin_export PRIVATE graphics/waveform_display_stub.cc)
endif()

target_link_libraries(coreproc_plugin_export PRIVATE cpputil metamodule::core-interface CoreModules)

if(NOT DEFINED METAMODULE_HEADLESS)
  target_link_libraries(coreproc_plugin_export PRIVATE ThorVG)
endif()

target_include_directories(coreproc_plugin_export PUBLIC ./)

target_compile_options(coreproc_plugin_export PRIVATE -fno-function-sections -fno-data-sections)

set_target_properties(coreproc_plugin_export PROPERTIES CXX_STANDARD 23)
