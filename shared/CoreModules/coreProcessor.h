#pragma once
#include "util/static_string.hh"
#include <array>
#include <memory>

// TODO: after switching to ModuleInfo
//  - remove Num*
//  - remove *Names
//  - maybe make *_name(idx) pure virtual constexpr
//
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

	static constexpr size_t NameChars = 15;
	static constexpr size_t LongNameChars = 39;

	static constexpr unsigned NumKnobs = 0;
	static constexpr unsigned NumOutJacks = 0;
	static constexpr unsigned NumInJacks = 0;
	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{};
	virtual StaticString<NameChars> knob_name(unsigned idx) {
		return (idx < NumKnobs) ? KnobNames[idx] : "";
	}
	virtual StaticString<NameChars> injack_name(unsigned idx) {
		return (idx < NumInJacks) ? InJackNames[idx] : "";
	}
	virtual StaticString<NameChars> outjack_name(unsigned idx) {
		return (idx < NumOutJacks) ? OutJackNames[idx] : "";
	}

	static inline const StaticString<LongNameChars> description{};
	virtual StaticString<LongNameChars> get_description() {
		return description;
	}

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

	virtual ~CoreProcessor() = default;
};
