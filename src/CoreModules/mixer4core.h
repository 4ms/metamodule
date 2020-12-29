#pragma once

#include "coreProcessor.h"
#include "math.hh"

using namespace MathTools;

class Mixer4Core : public CoreProcessor {
public:
	virtual void update() override
	{
		mixOut = 0;
		for (int i = 0; i < 4; i++) {
			mixOut += inputs[i] * levels[i];
		}
	}

	Mixer4Core() {}

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

	virtual void mark_all_inputs_unpatched() {}
	virtual void mark_input_unpatched(const int input_id) {}
	virtual void mark_input_patched(const int input_id) {}

	virtual void mark_all_outputs_unpatched() {}
	virtual void mark_output_unpatched(const int output_id) {}
	virtual void mark_output_patched(const int output_id) {}

private:
	float inputs[4];
	float levels[4];
	float mixOut;
};

