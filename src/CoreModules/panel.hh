#pragma once
#include "coreProcessor.h"

class Panel : public CoreProcessor {
public:
	static inline const int NumKnobs = 8;

	float inputs[4];
	float outputs[4];
	float params[NumKnobs];

public:
	Panel() {}

	virtual void set_param(const int param_id, const float val) override
	{
		if (param_id >= NumKnobs)
			return;
		params[param_id] = val;
	}

	virtual void set_input(const int jack_id, const float val) override
	{
		if (jack_id >= 4)
			return;
		inputs[jack_id] = val;
	}

	virtual float get_output(const int jack_id) const override
	{
		if (jack_id >= 4)
			return 0.f;

		return outputs[jack_id];
	}

	virtual void update() override {}
	virtual void set_samplerate(const float sr) override {}

	virtual void mark_all_inputs_unpatched() override {}
	virtual void mark_input_unpatched(const int input_id) override {}
	virtual void mark_input_patched(const int input_id) override {}

	virtual void mark_all_outputs_unpatched() override {}
	virtual void mark_output_unpatched(const int output_id) override {}
	virtual void mark_output_patched(const int output_id) override {}
};

