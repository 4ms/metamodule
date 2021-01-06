#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "CoreModules/moduleTypes.h"
#include "../processors/lpf.h"

using namespace MathTools;

class LowpassfilterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
	signalOut=lpf.update(signalIn);
	}

	LowpassfilterCore()
	{
	}

	virtual void set_param(int const param_id, const float val) override
	{
			lpf.set_param(param_id,val);
	}
	virtual void set_samplerate(const float sr) override
	{
		lpf.set_samplerate(sr);
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
			signalIn=val;
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
float signalIn=0;
float signalOut=0;
	
};
