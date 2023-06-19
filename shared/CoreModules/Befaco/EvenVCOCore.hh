#pragma once
#include "VCV-adaptor/VCVCoreProcessor.hh"
//
#include "VCV-adaptor/dsp/minblep.hpp"
#include "info/befaco/EvenVCO_info.hh"

struct EvenVCOCore : VCVCoreProcessor<MetaModule::EvenVCOInfo, EvenVCOCore> {
	using float_4 = float;
	static constexpr size_t PORT_MAX_CHANNELS = 1;

	static inline bool register_module = VCVCoreProcessor::s_registered;

	void process(const ProcessArgs &args) override;

	float_4 phase[4] = {};
	float_4 tri[4] = {};

	/** The value of the last sync input */
	float sync = 0.0;
	/** The outputs */
	/** Whether we are past the pulse width already */
	bool halfPhase[PORT_MAX_CHANNELS] = {};
	bool removePulseDC = true;

	rack::dsp::MinBlepGenerator<16, 32> triSquareMinBlep[PORT_MAX_CHANNELS];
	rack::dsp::MinBlepGenerator<16, 32> doubleSawMinBlep[PORT_MAX_CHANNELS];
	rack::dsp::MinBlepGenerator<16, 32> sawMinBlep[PORT_MAX_CHANNELS];
	rack::dsp::MinBlepGenerator<16, 32> squareMinBlep[PORT_MAX_CHANNELS];
};
