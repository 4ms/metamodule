#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "CoreModules/moduleTypes.h"
#include "../processors/lpf.h"
#include "../processors/tools/expDecay.h"

using namespace MathTools;

class LowpassgateCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
	    float slewedControl = expDecay.update(levelControl);
		lpf.set_param(0, slewedControl);
		signalOutput = (lpf.update(signalInput) * slewedControl);
	}

	LowpassgateCore()
	{
				lpf.set_param(1,0.0f);
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id == 0) {
			levelControl = val;
		}
		if (param_id == 1) {
			expDecay.decayTime = map_value(val, 0.F, 1.F, 10.F, 1000.0F);
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		lpf.set_samplerate(sr);
		expDecay.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
			signalInput=val;
		}
		
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
		case 0:
		output=signalOutput;
		break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<LowpassgateCore>();
	}
	static constexpr char typeID[20] = "LOWPASSGATE";
	static constexpr char description[] = "Low Pass Gate";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
    float signalInput=0;
	float signalOutput=0;
    LowPassFilter lpf;
	ExpDecay expDecay;
	float levelControl=1;
	
};
