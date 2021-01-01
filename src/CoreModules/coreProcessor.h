#pragma once
// #include "jack.h"

// class CoreModule {
// public:
// 	const int MAX_JACKS_PER_MODULE = 32;
// 	const int MAX_KNOBS_PER_MODULE = 32;

// 	using Jack = Jack_node;
// 	using Jacks = std::array<Jack, MAX_JACKS_PER_MODULE>;
// 	using Knob = float;
// 	using Knobs = std::array<Knob, MAX_KNOBS_PER_MODULE>;

// 	Jacks jacks;
// 	Knobs knobs;
// 	// Buttons?

// 	virtual void update() = 0;
// };

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

