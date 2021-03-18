#pragma once

#include "../processors/lpf.h"
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "util/math_tables.hh"

using namespace MathTools;

class LowpassfilterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		lpf.cutoff.setValue(setPitchMultiple(constrain(baseFrequency+cvInput*cvAmount,-1.0f,1.0f))*262.0f);
		signalOut = lpf.update(signalIn);
	}

	LowpassfilterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			baseFrequency=map_value(val,0.0f,1.0f,-1.0f,1.0f);
		} else if (param_id == 1) {
			lpf.q.setValue(map_value(val, 0.0f, 1.0f, 1.0f, 20.0f));
		} else if (param_id == 2) {
			cvAmount = val;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		lpf.sampleRate.setValue(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				signalIn = val;
				break;
			case 1:
				cvInput = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<LowpassfilterCore>();
	}
	static constexpr char typeID[20] = "LOWPASSFILTER";
	static constexpr char description[] = "Low Pass Filter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	LowPassFilter lpf;
	float signalIn = 0;
	float signalOut = 0;
	float baseFrequency=1.0;
	float cvInput=0;
	float cvAmount=0;
};
