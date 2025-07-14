cmake_minimum_required(VERSION 3.24)
project(CoreProc-Plugin)

add_library(coreproc_plugin_export STATIC)

target_sources(coreproc_plugin_export PRIVATE
	async_thread.cc
	
	audio/settings.cc

	dsp/block_resampler.cc
	dsp/stream_resampler.cc

	graphics/waveform_display.cc

	gui/notification.cc

	patch/patch.cc

	wav/wav_file_stream.cc
	wav/dr_wav.c

)

target_link_libraries(coreproc_plugin_export PRIVATE 
	cpputil 
	metamodule::core-interface
	CoreModules
)


target_include_directories(coreproc_plugin_export PUBLIC
	./
)

target_compile_options(coreproc_plugin_export PRIVATE 
	-fno-function-sections 
	-fno-data-sections
)

set_target_properties(coreproc_plugin_export PROPERTIES CXX_STANDARD 23)
