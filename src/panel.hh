#pragma once
#include "coreProcessor.h"

class Panel : public CoreProcessor {
	float inputs[4];
	float outputs[4];
	float params[8];

public:
	Panel() {}

	virtual void update() override
	{
		// send outputs[] -> codec and DACs
		// read codec and ADCs -> inputs[], params[]
	}

	virtual void set_param(const int param_id, const float val) override
	{
		// if (param_id >= 4)
		// 	return;
		// params[param_id] = val;
	}
	virtual void set_samplerate(const float sr) override {}

	virtual void set_input(const int jack_id, const float val) override
	{
		// Unlike normal modules, this function sets the value of the output jacks
		// because Panel outputs[] are the hardware outputs jacks, which are inputs to
		// the rest of the patch.
		if (jack_id >= 4)
			return;
		outputs[jack_id] = val;
	}

	virtual float get_output(const int jack_id) const override
	{
		// Unlike normal modules, this method returns the value of the input jacks
		// because Panel inputs[] are the hardware input jacks, which are outputs to
		// the rest of the patch.
		if (jack_id >= 4)
			return 0.f;

		return inputs[jack_id];
	}

	virtual void mark_all_inputs_unpatched() {}
	virtual void mark_input_unpatched(const int input_id) {}
	virtual void mark_input_patched(const int input_id) {}

	virtual void mark_all_outputs_unpatched() {}
	virtual void mark_output_unpatched(const int output_id) {}
	virtual void mark_output_patched(const int output_id) {}
};
