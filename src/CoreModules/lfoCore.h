#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"
#include <cmath>

using namespace MathTools;

class LFOCore : public CoreProcessor {
public:
	LFOCore() {}

	virtual void update() override
	{
		phaccu += frequency / sampleRate;
		if (phaccu >= 1.0f) {
			phaccu -= 1.0f;
		}
		if (resetInput > lastReset) {
			phaccu = 0;
		}
		// sinOut = sinf(2.0f * M_PI * (phaccu + phaseOffset)) * level;
		// sinOut = sinTable.interp_wrap(phaccu + phaseOffset) * level;
		sinOut = (phaccu + phaseOffset) * level;
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			knob_frequency = map_value(val, 0.0f, 1.0f, 0.1f, 20.0f);
			combineKnobCVFreq();
		}
		if (param_id == 1) {
			phaseOffset = val;
		}
		if (param_id == 2) {
			level = val;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		sampleRate = sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		if (input_id == 0) {
			cv_frequency = map_value(val, 0.0f, 1.0f, 0.1f, 20.0f);
			combineKnobCVFreq();
		}
		if (input_id == 1) {
			lastReset = resetInput;
			resetInput = (val > 0.0f);
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float value = 0;
		if (output_id == 0) {
			value = sinOut;
		}
		return value;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<LFOCore>();
	}
	static constexpr ModuleIDType get_module_type()
	{
		return ModuleType::LFO;
	}

private:
	static inline bool s_registered = ModuleFactory::registerModuleType(get_module_type(), "LFO", create);

private:
	float phaccu = 0;
	float phaseOffset = 0;
	float frequency = 1;
	float knob_frequency = 1;
	float cv_frequency = 1;
	float sampleRate = 48000;
	float level = 1;
	int resetInput = 0;
	int lastReset = 0;
	float sinOut;

	void combineKnobCVFreq()
	{
		frequency = knob_frequency + cv_frequency;
	}
};

