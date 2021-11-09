#pragma once
#include "CoreModules/info/buffmult_info.hh"
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"
#include "util/math_tables.hh"

class BuffMultCore : public CoreProcessor {
	using Info = BuffMultInfo;
	static constexpr int NumInJacks = Info::NumInJacks;
	static constexpr int NumOutJacks = Info::NumOutJacks;
	static constexpr int NumKnobs = Info::NumKnobs;

public:
	BuffMultCore() = default;

	void update() override {
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
		if (input_id < 0 || input_id > 1)
			return;
		in[input_id] = val;
	}

	void mark_all_inputs_unpatched() override {
		is_second_input_patched = false;
		in[0] = 0.f;
		in[1] = 0.f;
	}
	void mark_input_unpatched(int input_id) override {
		if (input_id == 0)
			in[0] = 0.f;
		if (input_id == 1) {
			in[1] = 0.f;
			is_second_input_patched = false;
		}
	}
	void mark_input_patched(int input_id) override {
		if (input_id == 1)
			is_second_input_patched = true;
	}

	float get_output(int output_id) const override {
		if (output_id < 0)
			return 0.f;
		if (output_id < 3 || !is_second_input_patched)
			return in[0];
		if (output_id < 6)
			return in[1];
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		switch (led_id) {
			case Info::LedInput_1_LED:
				return std::clamp(in[0], 0.f, 1.f);
			case Info::LedInput_2_LED:
				return std::clamp(is_second_input_patched ? in[1] : in[0], 0.f, 1.f);
			default:
				return 0.f;
		}
	}

	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<BuffMultCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, description, create);
	StaticString<NameChars> knob_name(unsigned idx) override { return (idx < Info::NumKnobs) ? Info::Knobs[idx].short_name : ""; }
	StaticString<NameChars> injack_name(unsigned idx) override { return (idx < Info::NumInJacks) ? Info::InJacks[idx].short_name: ""; }
	StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < Info::NumOutJacks) ? Info::OutJacks[idx].short_name : ""; }
	StaticString<LongNameChars> get_description() override { return Info::description; }
	// clang-format on

private:
	float in[2];
	bool is_second_input_patched = false;
};
