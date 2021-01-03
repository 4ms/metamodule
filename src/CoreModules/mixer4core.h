#pragma once

#include "coreProcessor.h"
#include "math.hh"
#include "moduleTypes.h"

using namespace MathTools;

class Mixer4Core : public CoreProcessor {
public:
	Mixer4Core() {}

	virtual void update() override
	{
		mixOut = 0;
		for (int i = 0; i < 4; i++) {
			mixOut += inputs[i] * levels[i];
		}
	}

	virtual void set_param(const int param_id, const float val) override
	{
		if (param_id >= 4)
			return;
		levels[param_id] = val;
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int input_id, const float val) override
	{
		if (input_id >= 4)
			return;
		inputs[input_id] = val;
	}

	virtual float get_output(const int output_id) const override
	{
		float output = 0;
		switch (output_id) {
			case 0:
				output = mixOut * -1;
				break;
			case 1:
				output = mixOut;
				break;
		}
		return output;
	}

	static std::unique_ptr<CoreProcessor> create()
	{
		return std::make_unique<Mixer4Core>();
	}

private:
	static inline bool s_registered = ModuleFactory::registerModuleType("MIXER4", "Mixer - 4 channel", create);

private:
	float inputs[4] = {0, 0, 0, 0};
	float levels[4] = {0, 0, 0, 0};
	float mixOut = 0;
};

