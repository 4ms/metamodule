#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class EightstepprobCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		cp.update();
		lastStep = currentStep;
		currentStep = cp.getCount() % 8;
		if (currentStep != lastStep) {
			randNum = randomNumber(0.0f, 0.99f);
		}
		if ((prob[currentStep] > randNum) && (cp.getWrappedPhase() < 0.5f)) {
			gateOutput = 1;
		} else {
			gateOutput = 0;
		}
	}

	EightstepprobCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		prob[param_id] = val;
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				cp.updateClock(val);
				break;
			case 1:
				cp.updateReset(val);
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

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<EightstepprobCore>();
	}
	static constexpr char typeID[20] = "EIGHTSTEPPROB";
	static constexpr char description[] = "8 Step Probability Sequencer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	float prob[8] = {1, 0, 0, 0, 0, 0, 0, 0};

	int gateOutput;

	int currentStep;
	int lastStep;

	float randNum = 0;
	ClockPhase cp;
};
