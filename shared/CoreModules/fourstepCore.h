#pragma once

#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "processors/stepsequencer.h"
#include "util/math.hh"

using namespace MathTools;

class FourstepCore : public CoreProcessor {
public:
	virtual void update(void) override
	{
		seq->update();
	}

	FourstepCore() {}

	virtual void set_param(int const param_id, const float val) override
	{
		seq->setStep(param_id, val);
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		switch (input_id) {
			case 0:
				seq->updateClock(val);
				break;
		}
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = seq->output;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<FourstepCore>();
	}
	static constexpr char typeID[20] = "FOURSTEP";
	static constexpr char description[] = "4 Step Sequencer";
	static inline bool s_registered = ModuleFactory::registerModuleType(typeID, description, create);

private:
	std::unique_ptr<StepSequencer> seq = std::make_unique<StepSequencer>(4);
};
