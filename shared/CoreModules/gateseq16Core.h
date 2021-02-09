#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/tools/clockPhase.h"

using namespace MathTools;

class Gateseq16Core : public CoreProcessor {
public:
	virtual void update(void) override {
		cp.update();
		stepPhase = cp.getWrappedPhase();
		currentStep = (int)(cp.getPhase())%16;
		if (stepActive[currentStep] && (stepPhase < 0.5f)) {
			gateOutput = 1;
		} else {
			gateOutput = 0;
		}
	}

	Gateseq16Core() {
			for (int i = 0; i < 16; i++) {
			stepActive[i] = false;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id > 15 || param_id < 0) {
			return;
		}

		stepActive[param_id] = val > 0.0f;
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
				output = gateOutput;
				break;
		}
		return output;
	}

	virtual float get_led_brightness(const int led_id) const override
	{
		bool stepStatus = stepActive[led_id];
		bool countStatus = (currentStep == led_id) && (stepPhase < 0.5f);
		return stepStatus ^ countStatus;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Gateseq16Core>();
	}
	static constexpr char typeID[20] = "GATESEQ16";
	static constexpr char description[] = "16 Step Gate Sequencer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ClockPhase cp;
	int currentStep = 0;
	float gateOutput = 0;
	bool stepActive[16];
	float stepPhase = 0;
};
