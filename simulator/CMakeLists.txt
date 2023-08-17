cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT LINUX)
set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(mm_sim LANGUAGES C CXX)

set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)
set(SIM_ROOT ${PROJECT_SOURCE_DIR})
set(LVGL_DIR ${MM_ROOT}/firmware/lib/lvgl/lvgl)

set(LV_CONF_PATH
    ${SIM_ROOT}/lv_conf.h
    CACHE STRING "" FORCE)

get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)

# #################### LVGL Simulator Driver #################################

add_subdirectory(lvgl_drv)

# #################### LVGL ############################################

include(${LVGL_DIR}/CMakeLists.txt)

# #################### Gui Assets ############################################
file(
  GLOB
  GUI_IMAGES
  ${MM_ROOT}/firmware/src/gui/images/4ms/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/4ms/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/Befaco/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/Befaco/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/AudibleInstruments/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/AudibleInstruments/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/hetrickcv/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/hetrickcv/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/Rack/components/*.c
  ${MM_ROOT}/firmware/src/gui/fonts/MuseoSansRounded_*.c)

# #################### SLS Export ##################################

file(STRINGS ${MM_ROOT}/firmware/src/gui/slsexport/meta5/filelist.txt
     SLS_SOURCES)
list(TRANSFORM SLS_SOURCES
     PREPEND "${MM_ROOT}/firmware/src/gui/slsexport/meta5/")

# Fixup for compiler warning in LVGL 8.3.4:
set_source_files_properties(${MM_ROOT}/firmware/src/gui/slsexport/meta5/ui.c
                            PROPERTIES COMPILE_FLAGS -Wno-unused-variable)

# #################### CoreModules ##################################
file(GLOB CORE_MODULES ${MM_ROOT}/shared/CoreModules/4ms/core/*Core.cc)

set(CORE_MODULES
    ${CORE_MODULES}
    ${MM_ROOT}/firmware/src/VCV_adaptor/plugin_instance.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
    #
    # Befaco
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/StereoStrip.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/SlewLimiter.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/SamplingModulator.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/STMix.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Rampage.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/PonyVCO.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Percall.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/MotionMTR.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Morphader.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Mixer.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Kickall.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/HexmixVCA.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/ChoppingKinky.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/ABC.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/ADSR.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/SpringReverb.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/DualAtenuverter.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/EvenVCO.cpp
    # ${MM_ROOT}/firmware/vcv-ports/Befaco/src/NoisePlethora.cpp
    # ${MM_ROOT}/firmware/vcv-ports/Befaco/src/Muxslicer.cpp
    #
    # AudibleInstruments
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/src/Braids.cpp
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/stmlib/utils/random.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/stmlib/dsp/atan.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/stmlib/dsp/units.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/analog_oscillator.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/digital_oscillator.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/macro_oscillator.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/resources.cc
    <<<<<<<
    HEAD
    #
    # HetrickCV
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/ASR.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma/src/arr.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma/src/Domain.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma/src/scl.cpp
    =======
    >>>>>>>
    f13f019d
    (Fix simulator CMakeList merge)
    #
    # HetrickCV
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/ASR.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/AToD.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/BinaryGate.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/BinaryNoise.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Bitshift.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Boolean3.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Chaos1Op.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Chaos2Op.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Chaos3Op.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/ChaoticAttractors.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/ClockedNoise.cpp
    # ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Comparator.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Contrast.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Crackle.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/DToA.cpp
    # ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/DataCompander.cpp
    # ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Delta.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Dust.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Exponent.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/FBSineChaos.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/FlipFlop.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/FlipPan.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/GateDelay.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/GateJunction.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/GateJunctionExp.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Gingerbread.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/LogicCombine.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/MidSide.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/MinMax.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhaseDrivenSequencer.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhaseDrivenSequencer32.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorAnalyzer.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorBurstGen.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorDivMult.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorEuclidean.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorGates.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorGates32.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorGates64.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorGen.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorGeometry.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorHumanizer.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorOctature.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorQuadrature.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorRandom.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorRanger.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorReset.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorRhythmGroup.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorShape.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorShift.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorStutter.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorSubstepShape.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorSwing.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorTimetable.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorToClock.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorToLFO.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/PhasorToWaveforms.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Polar.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Probability.cpp
    # ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/RandomGates.cpp
    # ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Rotator.cpp
    # ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Rungler.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Scanner.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/TwoToFour.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/VectorMix.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/Waveshape.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma/src/arr.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma/src/Domain.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma/src/scl.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/HetrickUtilities.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/DSP/HCVChaos.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/DSP/Phasors/HCVPhasorEffects.cpp
    ${MM_ROOT}/firmware/vcv_ports/hetrickcv/src/DSP/Phasors/HCVPhasorAnalyzers.cpp
    #
    # support files
    ${MM_ROOT}/firmware/src/VCV_adaptor/pffft/pffft.c
    ${MM_ROOT}/simulator/stubs/random.cpp
    ${MM_ROOT}/shared/axoloti-wrapper/axoloti_math.cpp
    ${MM_ROOT}/shared/cpputil/util/math_tables.cc)

# Fixups for compiler warnings in AudibleInstruments:
set_source_files_properties(
  ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/digital_oscillator.cc
  PROPERTIES COMPILE_OPTIONS
             "-Wno-unused-const-variable;-Wno-unused-but-set-variable")

# #################### RYML + Patch Convert ##################################

file(GLOB RYML_SOURCES
     ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/src/c4/yml/*.cpp
     ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/ext/c4core/src/c4/*.cpp)

add_library(
  ryml ${MM_ROOT}/shared/patch_convert/ryml/ryml_serial.cc
       ${MM_ROOT}/shared/patch_convert/yaml_to_patch.cc ${RYML_SOURCES})

target_include_directories(
  ryml
  PRIVATE ${MM_ROOT}/shared/patch_convert
          ${MM_ROOT}/shared/patch_convert/ryml
          ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/src
          ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/ext/c4core/src
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/simulator/stubs
          ${MM_ROOT}/shared)

target_compile_options(ryml PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>)

# #################### Application ############################################

add_executable(
  simulator src/main.cc src/ui.cc ${CORE_MODULES} ${GUI_IMAGES} ${SLS_SOURCES}
            ${MM_ROOT}/firmware/src/gui/pages/page_manager.cc)

target_include_directories(
  simulator
  PRIVATE src
          stubs
          lvgl_drv
          sdl_audio
          ${SDL2_INCLUDE_DIRS}
          ${MM_ROOT}
          ${MM_ROOT}/firmware
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/firmware/src/console
          ${MM_ROOT}/firmware/src/params
          ${MM_ROOT}/firmware/src/medium
          ${MM_ROOT}/shared
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/shared/patch
          ${MM_ROOT}/shared/CoreModules
          ${MM_ROOT}/shared/CoreModules/4ms
          ${MM_ROOT}/shared/CoreModules/Befaco
          ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack
          ${MM_ROOT}/firmware/vcv_ports/hetrickcv/Gamma
          ${MM_ROOT}/firmware/src/VCV_adaptor
          ${MM_ROOT}/firmware/src/VCV_adaptor/pffft)

target_compile_options(
  simulator PRIVATE -Wall -Og -g2 $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>
                    ${SDL2_CFLAGS_OTHER})
target_compile_options(simulator PRIVATE -Wno-missing-braces)

target_compile_definitions(simulator PRIVATE SIMULATOR TEST)
# Define TEST so braids dsp/dsp.h works (since it contains raw Cortex-M4
# assembly)

target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl lvgl::lvgl
                                        ryml SDL2)

#these link commands are provided by vcpkg as recommended for SDL2.
#leaving these here temporarily in case linking fails when we get there.
#target_link_libraries(simulator
#        PRIVATE
#        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
#        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
#)

message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_options(simulator PUBLIC "-Wl,-map,simulator.map")
  else()
    target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(simulator PRIVATE "/MAP:simulator.map")
endif()
