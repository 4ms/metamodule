#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "math.hh"
#include "processors/tools/clockPhase.h"

using namespace MathTools;

class Gateseq8Core : public CoreProcessor {
public:
	virtual void update(void) override
	{

		cp.update();
		currentStep = (int)(cp.getPhase())%8;
		if (stepActive[currentStep] && (cp.getWrappedPhase() < 0.5f)) {
			gateOutput = 1;
		} else {
			gateOutput = 0;
		}
	}

	Gateseq8Core()
	{
		for (int i = 0; i < 8; i++) {
			stepActive[i] = false;
		}
	}

	virtual void set_param(int const param_id, const float val) override
	{
		if (param_id > 7 || param_id < 0) {
			return;
		}

		stepActive[param_id] = val > 0.0f;
	}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cp.updateClock(val);
				break;
		}
	}

	virtual void set_samplerate(const float sr) override
	{
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
		return stepActive[led_id];
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Gateseq8Core>();
	}
	static constexpr char typeID[20] = "GATESEQ8";
	static constexpr char description[] = "8 Step Gate Sequencer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	ClockPhase cp;
	int currentStep = 0;
	float gateOutput = 0;
	bool stepActive[8];
};
