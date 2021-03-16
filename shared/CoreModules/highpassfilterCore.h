#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/hpf.h"

using namespace MathTools;

class HighpassfilterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		hpf.cutoff = map_value(cutoffOffset, 0.0f, 1.0f, 20.0f, 20000.0f);
		signalOutput = hpf.update(signalInput);
	}

	HighpassfilterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				cutoffOffset = val * val;
				break;
			case 1:
				hpf.q = map_value(val, 0.0f, 1.0f, 1.0f, 20.0f);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		hpf.sampleRate = sr;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalInput = val;
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
		return std::make_unique<HighpassfilterCore>();
	}
	static constexpr char typeID[20] = "HIGHPASSFILTER";
	static constexpr char description[] = "Highpass Filter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	HighPassFilter hpf;
	float signalInput = 0;
	float signalOutput = 0;
	float cutoffOffset = 0;
	float cutoffCV = 0;
};
