#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/bpf.h"

using namespace MathTools;

class BandpassfilterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		bpf.cutoff.setValue(262.0f * setPitchMultiple(constrain(cutoffCV + cutoffOffset, -1.0f, 1.0f)));
		signalOutput = bpf.update(signalInput);
	}

	BandpassfilterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				cutoffOffset = map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case 1:
				bpf.q = map_value(val, 0.0f, 1.0f, 1.0f, 20.0f);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		bpf.sampleRate.setValue(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
				break;
			case 1:
				cutoffCV = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<BandpassfilterCore>();
	}
	static constexpr char typeID[20] = "BANDPASSFILTER";
	static constexpr char description[] = "Bandpass Filter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	BandPassFilter bpf;
	float cutoffCV = 0;
	float cutoffOffset = 0;
	float signalInput = 0;
	float signalOutput = 0;
};
