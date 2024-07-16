cmake_minimum_required(VERSION 3.22)

if(BUILD_DYN_PLUGIN)
	include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)
endif()

#########################################################
# Step 2: Define your project name, vesion, etc
project(RackFundamentalMetaModulePlugin
    VERSION     0.1
    DESCRIPTION "Fundamental Plugin for MetaModule"
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(RackLibrary STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Rack/src)

target_sources(RackLibrary
    PRIVATE

	${SOURCE_DIR}/8vert.cpp
	${SOURCE_DIR}/ADSR.cpp
	${SOURCE_DIR}/CVMix.cpp
	${SOURCE_DIR}/Compare.cpp
	# ${SOURCE_DIR}/Delay.cpp #src_new src_delete src_process
	${SOURCE_DIR}/Fade.cpp
	${SOURCE_DIR}/Gates.cpp
	${SOURCE_DIR}/LFO.cpp
	${SOURCE_DIR}/Logic.cpp
	# ${SOURCE_DIR}/Merge.cpp #not relevent without polyphony
	${SOURCE_DIR}/MidSide.cpp
	${SOURCE_DIR}/Mixer.cpp
	${SOURCE_DIR}/Mult.cpp
	${SOURCE_DIR}/Mutes.cpp
	${SOURCE_DIR}/Noise.cpp
	${SOURCE_DIR}/Octave.cpp
	${SOURCE_DIR}/Process.cpp
	${SOURCE_DIR}/Pulses.cpp
	${SOURCE_DIR}/Push.cpp
	${SOURCE_DIR}/Quantizer.cpp
	${SOURCE_DIR}/Random.cpp
	${SOURCE_DIR}/RandomValues.cpp
	${SOURCE_DIR}/Rescale.cpp
	${SOURCE_DIR}/SEQ3.cpp
	${SOURCE_DIR}/SHASR.cpp
	# ${SOURCE_DIR}/Scope.cpp # screens don't work in MM
	${SOURCE_DIR}/SequentialSwitch.cpp
	# ${SOURCE_DIR}/Split.cpp # not relevent without polyphony
	${SOURCE_DIR}/Sum.cpp
	${SOURCE_DIR}/Unity.cpp
	${SOURCE_DIR}/VCA-1.cpp
	${SOURCE_DIR}/VCA.cpp
	${SOURCE_DIR}/VCF.cpp
	${SOURCE_DIR}/VCMixer.cpp
	${SOURCE_DIR}/VCO.cpp
	# ${SOURCE_DIR}/Viz.cpp #not relevent without polyphony

	# Uses filesystem:
	# ${SOURCE_DIR}/WTLFO.cpp
	# ${SOURCE_DIR}/WTVCO.cpp
	# ${SOURCE_DIR}/dr_wav.c

	# ${SOURCE_DIR}/plugin.cpp
	plugin.cpp
)

target_include_directories(RackLibrary PRIVATE
    ${SOURCE_DIR}/
    .
)

target_compile_options(RackLibrary PRIVATE
    -fexceptions
    -Wno-deprecated-enum-enum-conversion
)

set_property(TARGET RackLibrary PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
if(BUILD_DYN_PLUGIN)
create_plugin(
    SOURCE_LIB      RackLibrary                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Fundamental                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Fundamental # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
endif()
