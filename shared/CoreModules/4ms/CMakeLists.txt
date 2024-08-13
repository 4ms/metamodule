add_library(CoreModules-4ms STATIC)

target_compile_features(CoreModules-4ms PUBLIC cxx_std_23)

file(GLOB CORE_SOURCES core/*Core.cc)

target_sources(CoreModules-4ms PRIVATE 
	${CORE_SOURCES}

	core/enosc/data.cc
	core/enosc/dynamic_data.cc
	# core/enosc/easiglib/numtypes.cc
	core/axoloti-wrapper/axoloti_math.cpp
	core/tapo/multitap_delay.cc
	core/tapo/resources.cc
	core/tapo/tap_allocator.cc
	core/tapo/control.cc
	core/tapo/ui.cc
	core/tapo/stmlib/utils/random.cc
	core/tapo/stmlib/dsp/units.cc
	core/looping-delay/src/calibration_storage.cc
	core/qplfo/qplfo.cc
	core/qplfo/qplfo_mocks.cc
	core/peg-common/peg_base.cc
	core/peg-common/trigout.cc
	core/peg-common/analog_conditioning.cc
	core/peg-common/env_update.cc
	core/peg-common/envelope_calcs.cc
	core/peg-common/flash_user.cc
	core/peg-common/params.cc
	core/peg-common/pingable_env.cc
	core/peg-common/dig_inouts.cc
	core/peg-common/timers.cc
	core/peg-common/calibration.cc
	core/peg-common/env_transition.cc
	core/peg-common/leds.cc
	core/peg-common/shareddrv/debounced_digins.cc
	core/peg-common/shareddrv/dac.cc
	core/peg-common/pwm.cc
	core/mpeg/envelope_calcs.cc
	core/peg/envelope_calcs.cc
)

target_include_directories(CoreModules-4ms PUBLIC 
	./
	core/tapo/stmlib
	core/tapo/
	core/alpaca/include
	core/looping-delay/src
	core/
	core/peg-common/
	core/peg-common/mocks
)


target_compile_definitions(CoreModules-4ms PRIVATE 
	TEST     
	SAMPLE_RATE=48000
)

target_compile_options(CoreModules-4ms PRIVATE
    -Wno-double-promotion #silence warnings in gcem
)

set_property(TARGET CoreModules-4ms PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

if (NOT DEFINED alpaca)
  add_subdirectory(core/alpaca)
  target_compile_definitions(alpaca INTERFACE ALPACA_NO_PREFETCH)
endif()

target_link_libraries(CoreModules-4ms PUBLIC 
	cpputil 
	ryml 
	alpaca
	CoreModules
	metamodule::core-interface
	metamodule::patch-serial
)

