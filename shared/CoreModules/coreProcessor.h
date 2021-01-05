#pragma once
#include <memory>

class CoreProcessor {
public:
	virtual void update() = 0;
	virtual void set_samplerate(const float sr) = 0;
	virtual void set_param(const int param_id, const float val) = 0;
	virtual void set_input(const int input_id, const float val) = 0;
	virtual float get_output(const int output_id) const = 0;

	virtual void mark_all_inputs_unpatched() {}
	virtual void mark_input_unpatched(const int input_id) {}
	virtual void mark_input_patched(const int input_id) {}

	virtual void mark_all_outputs_unpatched() {}
	virtual void mark_output_unpatched(const int output_id) {}
	virtual void mark_output_patched(const int output_id) {}

	virtual ~CoreProcessor() {}
};

