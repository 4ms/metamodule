#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/module_info_base.hh"

struct MetaModuleInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"MetaModule"};
	static constexpr std::string_view description{"MetaModule"};
	static constexpr uint32_t width_hp = 26;
	static constexpr std::string_view svg_filename{"res/modules/MetaModule-artwork.svg"};

	static constexpr int NumKnobs = 12;

	enum {
		KnobA = 0,
		KnobB = 1,
		KnobC = 2,
		KnobD = 3,
		KnobE = 4,
		KnobF = 5,
		KnobU = 6,
		KnobV = 7,
		KnobW = 8,
		KnobX = 9,
		KnobY = 10,
		KnobZ = 11,
	};

	static constexpr std::array<KnobDef, NumKnobs> Knobs{{
		{
			.id = KnobA,
			.x_mm = px_to_mm<72>(32.89f),
			.y_mm = px_to_mm<72>(213.17f),
			.short_name = "A",
			.long_name = "A",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobB,
			.x_mm = px_to_mm<72>(92.87f),
			.y_mm = px_to_mm<72>(201.73f),
			.short_name = "B",
			.long_name = "B",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobC,
			.x_mm = px_to_mm<72>(153.77f),
			.y_mm = px_to_mm<72>(213.17f),
			.short_name = "C",
			.long_name = "C",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobD,
			.x_mm = px_to_mm<72>(218.71f),
			.y_mm = px_to_mm<72>(213.17f),
			.short_name = "D",
			.long_name = "D",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobE,
			.x_mm = px_to_mm<72>(279.38f),
			.y_mm = px_to_mm<72>(201.83f),
			.short_name = "E",
			.long_name = "E",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobF,
			.x_mm = px_to_mm<72>(340.01f),
			.y_mm = px_to_mm<72>(213.17f),
			.short_name = "F",
			.long_name = "F",
			.default_val = 0.0f,
			.knob_style = KnobDef::Medium,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobU,
			.x_mm = px_to_mm<72>(26.58f),
			.y_mm = px_to_mm<72>(61.85f),
			.short_name = "u",
			.long_name = "u",
			.default_val = 0.0f,
			.knob_style = KnobDef::Small,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobV,
			.x_mm = px_to_mm<72>(61.07f),
			.y_mm = px_to_mm<72>(110.02f),
			.short_name = "v",
			.long_name = "v",
			.default_val = 0.0f,
			.knob_style = KnobDef::Small,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobW,
			.x_mm = px_to_mm<72>(26.6f),
			.y_mm = px_to_mm<72>(157.86f),
			.short_name = "w",
			.long_name = "w",
			.default_val = 0.0f,
			.knob_style = KnobDef::Small,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobX,
			.x_mm = px_to_mm<72>(345.28f),
			.y_mm = px_to_mm<72>(91.46f),
			.short_name = "x",
			.long_name = "x",
			.default_val = 0.0f,
			.knob_style = KnobDef::Small,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobY,
			.x_mm = px_to_mm<72>(302.03f),
			.y_mm = px_to_mm<72>(123.31f),
			.short_name = "y",
			.long_name = "y",
			.default_val = 0.0f,
			.knob_style = KnobDef::Small,
			.orientation = KnobDef::Round,
		},
		{
			.id = KnobZ,
			.x_mm = px_to_mm<72>(345.31f),
			.y_mm = px_to_mm<72>(157.07f),
			.short_name = "z",
			.long_name = "z",
			.default_val = 0.0f,
			.knob_style = KnobDef::Small,
			.orientation = KnobDef::Round,
		},
	}};

	static constexpr int NumInJacks = 8;

	enum {
		InputIn1 = 0,
		InputIn2 = 1,
		InputIn3 = 2,
		InputIn4 = 3,
		InputIn5 = 4,
		InputIn6 = 5,
		InputGatein1 = 6,
		InputGatein2 = 7,
	};

	static constexpr std::array<InJackDef, NumInJacks> InJacks{{
		{
			.id = InputIn1,
			.x_mm = px_to_mm<72>(35.03f),
			.y_mm = px_to_mm<72>(323.62f),
			.short_name = "in1",
			.long_name = "in1",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Analog,
		},
		{
			.id = InputIn2,
			.x_mm = px_to_mm<72>(78.54f),
			.y_mm = px_to_mm<72>(323.62f),
			.short_name = "in2",
			.long_name = "in2",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Analog,
		},
		{
			.id = InputIn3,
			.x_mm = px_to_mm<72>(121.2f),
			.y_mm = px_to_mm<72>(323.86f),
			.short_name = "in3",
			.long_name = "in3",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Analog,
		},
		{
			.id = InputIn4,
			.x_mm = px_to_mm<72>(164.86f),
			.y_mm = px_to_mm<72>(323.86f),
			.short_name = "in4",
			.long_name = "in4",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Analog,
		},
		{
			.id = InputIn5,
			.x_mm = px_to_mm<72>(108.32f),
			.y_mm = px_to_mm<72>(282.34f),
			.short_name = "in5",
			.long_name = "in5",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Analog,
		},
		{
			.id = InputIn6,
			.x_mm = px_to_mm<72>(150.84f),
			.y_mm = px_to_mm<72>(282.34f),
			.short_name = "in6",
			.long_name = "in6",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Analog,
		},
		{
			.id = InputGatein1,
			.x_mm = px_to_mm<72>(21.74f),
			.y_mm = px_to_mm<72>(274.18f),
			.short_name = "gatein1",
			.long_name = "gatein1",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Gate,
		},
		{
			.id = InputGatein2,
			.x_mm = px_to_mm<72>(65.25f),
			.y_mm = px_to_mm<72>(274.2f),
			.short_name = "gatein2",
			.long_name = "gatein2",
			.unpatched_val = 0.f,
			.signal_type = InJackDef::Gate,
		},
	}};

	static constexpr int NumOutJacks = 8;

	enum {
		OutputOut1 = 0,
		OutputOut2 = 1,
		OutputOut3 = 2,
		OutputOut4 = 3,
		OutputOut5 = 4,
		OutputOut6 = 5,
		OutputOut7 = 6,
		OutputOut8 = 7,
	};

	static constexpr std::array<OutJackDef, NumOutJacks> OutJacks{{
		{
			.id = OutputOut1,
			.x_mm = px_to_mm<72>(208.16f),
			.y_mm = px_to_mm<72>(323.62f),
			.short_name = "out1",
			.long_name = "out1",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut2,
			.x_mm = px_to_mm<72>(251.6f),
			.y_mm = px_to_mm<72>(323.86f),
			.short_name = "out2",
			.long_name = "out2",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut3,
			.x_mm = px_to_mm<72>(294.05f),
			.y_mm = px_to_mm<72>(323.62f),
			.short_name = "out3",
			.long_name = "out3",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut4,
			.x_mm = px_to_mm<72>(337.49f),
			.y_mm = px_to_mm<72>(323.62f),
			.short_name = "out4",
			.long_name = "out4",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut5,
			.x_mm = px_to_mm<72>(221.02f),
			.y_mm = px_to_mm<72>(282.17f),
			.short_name = "out5",
			.long_name = "out5",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut6,
			.x_mm = px_to_mm<72>(264.39f),
			.y_mm = px_to_mm<72>(282.17f),
			.short_name = "out6",
			.long_name = "out6",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut7,
			.x_mm = px_to_mm<72>(307.65f),
			.y_mm = px_to_mm<72>(281.86f),
			.short_name = "out7",
			.long_name = "out7",
			.signal_type = OutJackDef::Analog,
		},
		{
			.id = OutputOut8,
			.x_mm = px_to_mm<72>(351.09f),
			.y_mm = px_to_mm<72>(281.86f),
			.short_name = "out8",
			.long_name = "out8",
			.signal_type = OutJackDef::Analog,
		},
	}};

	static constexpr int NumSwitches = 4;

	enum {
		SwitchCc = 0,
		SwitchGate = 1,
		SwitchNote = 2,
		SwitchSave = 3,
	};

	static constexpr std::array<SwitchDef, NumSwitches> Switches{{
		{
			.id = SwitchCc,
			.x_mm = px_to_mm<72>(69.525f),
			.y_mm = px_to_mm<72>(80.075f),
			.short_name = "CC",
			.long_name = "CC",
			.switch_type = SwitchDef::Toggle3pos,
			.orientation = SwitchDef::Horizontal,
			.encoder_knob_style = SwitchDef::None,
		},
		{
			.id = SwitchGate,
			.x_mm = px_to_mm<72>(69.525f),
			.y_mm = px_to_mm<72>(60.285f),
			.short_name = "Gate",
			.long_name = "Gate",
			.switch_type = SwitchDef::Toggle3pos,
			.orientation = SwitchDef::Horizontal,
			.encoder_knob_style = SwitchDef::None,
		},
		{
			.id = SwitchNote,
			.x_mm = px_to_mm<72>(69.525f),
			.y_mm = px_to_mm<72>(40.585f),
			.short_name = "Note",
			.long_name = "Note",
			.switch_type = SwitchDef::Toggle3pos,
			.orientation = SwitchDef::Horizontal,
			.encoder_knob_style = SwitchDef::None,
		},
		{
			.id = SwitchSave,
			.x_mm = px_to_mm<72>(352.2f),
			.y_mm = px_to_mm<72>(43.24f),
			.short_name = "SAVE",
			.long_name = "SAVE",
			.switch_type = SwitchDef::LatchingButton,
			.orientation = SwitchDef::Round,
			.encoder_knob_style = SwitchDef::None,
		},
	}};

	static constexpr int NumDiscreteLeds = 0;

	static constexpr std::array<LedDef, NumDiscreteLeds> Leds{{}};
};
