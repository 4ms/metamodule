#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class Switch4to1Core : public CoreProcessor {
public:
	virtual void update(void) override
	{
		cp.update();
		stepNum = cp.getCount() % 4;
	}

	Switch4to1Core() {}

	virtual void set_param(int const param_id, const float val) override
	{
		switch (param_id) {
		}
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		if (input_id == 0) {
			cp.updateClock(val);
		} else if (input_id == 1) {
			cp.updateReset(val);
		} else {
			auto inputNum = input_id - 2;
			signalInputs[inputNum] = val;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = signalInputs[stepNum];
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Switch4to1Core>();
	}
	static constexpr char typeID[20] = "SWITCH4TO1";
	static constexpr char description[] = "4 to 1 Switch";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	int stepNum = 0;
	float signalInputs[4] = {0, 0, 0, 0};
	ClockPhase cp;
};
