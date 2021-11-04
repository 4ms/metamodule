#pragma once
#include "CoreModules/defs/defs_template.hh"
#include "CoreModules/moduleTypes.h"
#include "coreProcessor.h"
#include "util/math.hh"
#include "util/math_tables.hh"

// EnOscDefs.hh:

struct EnOscDefs : ModuleDefsBase {
	static constexpr auto NameChars = CoreProcessor::NameChars;
	static constexpr auto LongNameChars = CoreProcessor::LongNameChars;

	static constexpr std::string_view slug{"EnOsc"};
	static constexpr uint32_t width_hp = 16;
	static constexpr std::string_view svg_filename{"res/16hptemplate.svg"};
	// static constexpr std::string_view svg_filename{"res/EnOsc-artwork.svg"};

	static constexpr int NumKnobs = 9;
	static constexpr int NumInJacks = 10;
	static constexpr int NumOutJacks = 2;
	static constexpr int NumSwitches = 6;

	static constexpr std::array<KnobDef, NumKnobs> Knobs{{
		{.id = 0,
		 .x = mm2um(77.47f),
		 .y = mm2um(52.85f),
		 .default_val = 0.f,
		 .knob_type = KnobDef::Medium,
		 .short_name = "Scale",
		 .long_name = "Scale",
		 .description = "Scale Selection 1-10"},
		{.id = 1,
		 .x = mm2um(61.09f),
		 .y = mm2um(114.45),
		 .default_val = 0.5f,
		 .knob_type = KnobDef::Medium,
		 .short_name = "Spread",
		 .long_name = "Spread",
		 .description = "Oscillator Spread"},
	}};

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{
		"Scale",
		"Spread",
		"Pitch",
		"Balance",
		"Root",
		"Cross FM",
		"Twist",
		"Detune",
		"Warp",
	};
	static inline const std::array<StaticString<NameChars>, NumInJacks> InJackNames{
		"PitchCV",
		"RootCV",
		"ScaleCV",
		"SpreadCV",
		"CrossCV",
		"BalanceCV",
		"TwistCV",
		"WarpCV",
		"LearnTrig",
		"FreezeTrig",
	};
	static inline const std::array<StaticString<NameChars>, NumOutJacks> OutJackNames{
		"Out A",
		"Out B",
	};
	static inline const std::array<StaticString<NameChars>, NumSwitches> SwitchNames{
		"Scale",
		"Cross",
		"Twist",
		"Warp",
		"Learn",
		"Freeze",
	};

	static inline const StaticString<LongNameChars> description{"Ensemble Oscillator"};
};

// Generator:
// SLUG = EnOsc

class EnOscCore : public CoreProcessor { //{SLUG}Core
	using Info = EnOscDefs;				 //{SLUG}Defs
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

	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<EnOscCore>(); } //{SLUG}Core
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, description, create);
	constexpr StaticString<NameChars> knob_name(unsigned idx) override { return (idx < Info::NumKnobs) ? Info::KnobNames[idx] : ""; }
	constexpr StaticString<NameChars> injack_name(unsigned idx) override { return (idx < Info::NumInJacks) ? Info::InJackNames[idx] : ""; }
	constexpr StaticString<NameChars> outjack_name(unsigned idx) override { return (idx < Info::NumOutJacks) ? Info::OutJackNames[idx] : ""; }
	constexpr StaticString<LongNameChars> get_description() override { return Info::description; }
	// clang-format on

private:
	// local vars here
};
