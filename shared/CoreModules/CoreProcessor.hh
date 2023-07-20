#pragma once
#include <string_view>

class CoreProcessor {
public:
	CoreProcessor() = default;

	virtual void update() = 0;
	virtual void set_samplerate(const float sr) = 0;
	virtual void set_param(const int param_id, const float val) = 0;
	virtual void set_input(const int input_id, const float val) = 0;
	virtual float get_output(const int output_id) const = 0;
	virtual float get_led_brightness(const int led_id) const {
		return 0;
	}
	virtual void set_alt_param(const int alt_param_id, const float val) {
	}

	// Given an unscaled val: 0 <= val <= 1,
	// apply scaling (range and offset) to val
	virtual void set_and_scale_param(int param_id, float val) {
		set_param(param_id, val);
	}

	static constexpr unsigned NameChars = 15;
	static constexpr unsigned LongNameChars = 39;

	virtual void mark_all_inputs_unpatched() {
	}
	virtual void mark_input_unpatched(const int input_id) {
	}
	virtual void mark_input_patched(const int input_id) {
	}
	virtual void mark_all_outputs_unpatched() {
	}
	virtual void mark_output_unpatched(const int output_id) {
	}
	virtual void mark_output_patched(const int output_id) {
	}
	virtual constexpr std::string_view get_alt_param_value(unsigned alt_id, float val) {
		return "-";
	}

	virtual ~CoreProcessor() = default;
};
