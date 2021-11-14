#pragma once
#include "CoreModules/info/EnOsc_info.hh"
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"
#include "util/math_tables.hh"

class EnOscCore : public CoreProcessor {
	using Info = EnOscInfo;
	static constexpr int NumInJacks = Info::NumInJacks;
	static constexpr int NumOutJacks = Info::NumOutJacks;
	static constexpr int NumKnobs = Info::NumKnobs;

public:
	EnOscCore() = default;

	void update() override {
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
	}

	float get_output(int output_id) const override {
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		switch (led_id) {
			case Info::SwitchLearn * 3 + 0:
				return 0.75f;
				break;
			case Info::SwitchLearn * 3 + 1:
				return 0.40f;
				break;
			case Info::SwitchLearn * 3 + 2:
				return 0.f;
				break;
			case Info::SwitchFreeze * 3 + 0:
				return 0.00f;
				break;
			case Info::SwitchFreeze * 3 + 1:
				return 0.20f;
				break;
			case Info::SwitchFreeze * 3 + 2:
				return 0.9f;
				break;

			default:
				return 0.f;
		}
	}

	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<EnOscCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, description, create, enoscinfo);
	StaticString<NameChars> knob_name(unsigned idx) override { return (idx < Info::NumKnobs) ? Info::Knobs[idx].short_name : ""; }
	StaticString<NameChars> injack_name(unsigned idx) override { return (idx < Info::NumInJacks) ? Info::InJacks[idx].short_name: ""; }
	StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < Info::NumOutJacks) ? Info::OutJacks[idx].short_name : ""; }
	StaticString<LongNameChars> get_description() override { return Info::description; }
	// clang-format on

private:
	// local vars here
};
