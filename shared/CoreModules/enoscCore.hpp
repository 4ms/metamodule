#pragma once
#include "CoreModules/info/enoscInfo.hh" //{slug}Info.hh
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"
#include "util/math_tables.hh"

// Generator: SLUG = EnOsc
// TODO: can we make this a template of type EnOscDefs ?

class EnOscCore : public CoreProcessor { //{SLUG}Core
	using Info = EnOscInfo;				 //{SLUG}Info
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

	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<EnOscCore>(); } //{SLUG}Core
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, description, create);
	StaticString<NameChars> knob_name(unsigned idx) override { return (idx < Info::NumKnobs) ? Info::KnobNames[idx] : ""; }
	StaticString<NameChars> injack_name(unsigned idx) override { return (idx < Info::NumInJacks) ? Info::InJackNames[idx] : ""; }
	StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < Info::NumOutJacks) ? Info::OutJackNames[idx] : ""; }
	StaticString<LongNameChars> get_description() override { return Info::description; }
	// clang-format on

private:
	// local vars here
};
