#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/tools/expDecay.h"

using namespace MathTools;

class SlewlimiterCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		signalOutput = slew.update(signalInput);
	}

	SlewlimiterCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0: // rise time

				break;
			case 1: // fall time
				slew.decayTime = map_value(val, 0.0f, 1.0f, 1.0f, 2000.0f);
				break;
		}
	}
	virtual void set_samplerate(const float sr) override
	{
		slew.set_samplerate(sr);
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
		return std::make_unique<SlewlimiterCore>();
	}
	static constexpr char typeID[20] = "SLEWLIMITER";
	static constexpr char description[] = "Slew Limiter";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ExpDecay slew;
	float signalInput = 0;
	float signalOutput = 0;
};
