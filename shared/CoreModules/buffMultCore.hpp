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
	}

	float get_output(int output_id) const override {
		return 0.f;
	}

	void set_samplerate(float sr) override {
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
	// local vars here
};
