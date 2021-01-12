#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/tools/clockPhase.h"

using namespace MathTools;

class ClkmultiplierCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		cp.update();
		if (cp.getWrappedPhase() < pulseWidth) {
			clockOutput = 1;
		} else {
			clockOutput = 0;
		}
	}

	ClkmultiplierCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
			case 0:
				cp.setMultiply(map_value(val, 0.0f, 1.0f, 1.0f, 8.99f));
				break;
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cp.updateClock(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = clockOutput;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<ClkmultiplierCore>();
	}
	static constexpr char typeID[20] = "CLKMULTIPLIER";
	static constexpr char description[] = "clock multiplier";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int clkMult = 4;
	float cvIn = 0;
	float pulseWidth = 0.5f;
	int clockOutput = 0;

	ClockPhase cp;
};
