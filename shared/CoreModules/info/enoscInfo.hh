#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/module_info_base.hh"

struct EnOscInfo : ModuleInfoBase { //{SLUG}Info
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
		{
			.id = 0,
			.x_mm = px_to_mm<72>(53.68f),
			.y_mm = px_to_mm<72>(78.08f),
			.default_val = 0.f,
			.knob_style = KnobDef::Medium,
			.short_name = "Scale",
			.long_name = "Scale",
		},
		{
			.id = 1,
			.x_mm = px_to_mm<72>(114.85f),
			.y_mm = px_to_mm<72>(61.59f),
			.default_val = 0.5f,
			.knob_style = KnobDef::Medium,
			.short_name = "Spread",
			.long_name = "Spread",
		},
	}};

	/// not used:
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
