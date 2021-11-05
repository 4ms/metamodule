#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/defs/defs_template.hh"

// EnOscDefs.hh: //{SLUG}Defs.hh

struct EnOscDefs : ModuleDefsBase { //{SLUG}Defs
	static constexpr auto NameChars = CoreProcessor::NameChars;
	static constexpr auto LongNameChars = CoreProcessor::LongNameChars;

	static constexpr std::string_view slug{"EnOsc"}; //{SLUG}
	static constexpr uint32_t width_hp = 16;
	static constexpr std::string_view svg_filename{"res/16hptemplate.svg"}; // res/{SLUG}-artwork.svg
	// static constexpr std::string_view svg_filename{"res/EnOsc-artwork.svg"};

	static constexpr int NumKnobs = 2; // 9;
	static constexpr int NumInJacks = 10;
	static constexpr int NumOutJacks = 2;
	static constexpr int NumSwitches = 6;

	static constexpr std::array<KnobDef, NumKnobs> Knobs{{
		{.id = 0,
		 .x = 77.47f,
		 .y = 52.85f,
		 .default_val = 0.f,
		 .knob_type = KnobDef::Medium,
		 .short_name = "Scale",
		 .long_name = "Scale",
		 .description = "Scale Selection 1-10"},
		{.id = 1,
		 .x = 61.09f,
		 .y = 114.45,
		 .default_val = 0.5f,
		 .knob_type = KnobDef::Medium,
		 .short_name = "Spread",
		 .long_name = "Spread",
		 .description = "Oscillator Spread"},
	}};

	static inline const std::array<StaticString<NameChars>, NumKnobs> KnobNames{
		"Scale", "Spread",
		// "Pitch",
		// "Balance",
		// "Root",
		// "Cross FM",
		// "Twist",
		// "Detune",
		// "Warp",
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
