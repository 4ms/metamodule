#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class Switch1to4Core : public CoreProcessor {
public:
	virtual void update(void) override
	{
		cp.update();
		stepNum = cp.getCount() % 4;
	}

	Switch1to4Core() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0: // clock
				cp.updateClock(val);
				break;
			case 1: // reset
				cp.updateReset(val);
				break;
			case 2: // signal
				inputSignal = val;
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		if (output_id == stepNum) {
			output = inputSignal;
		} else {
			output = 0;
		}

		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Switch1to4Core>();
	}
	static constexpr char typeID[20] = "SWITCH1TO4";
	static constexpr char description[] = "1 to 4 Switch";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ClockPhase cp;
	int stepNum = 0;
	float inputSignal = 0;
};
