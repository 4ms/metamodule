#pragma once
#include <cstdint>
#include <span>
#include <vector>

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

	virtual void load_state(std::span<const uint8_t> state_data) {
	}
	virtual std::vector<uint8_t> save_state() {
		return {};
	}

	virtual ~CoreProcessor() = default;

	// common default values, OK to override or ignored
	static constexpr float CvRangeVolts = 5.0f;
	static constexpr float MaxOutputVolts = 8.0f;
};
