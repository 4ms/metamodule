#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct EnOscInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"EnOsc"};
	static constexpr std::string_view description{"Ensemble Oscillator"};
	static constexpr uint32_t width_hp = 16;
	static constexpr bool uses_center_coords = true;
	static constexpr std::string_view svg_filename{"res/modules/EnOsc-artwork.svg"};

	static constexpr std::array<Element, 27> Elements{{
		Davies1900hBlackKnob{to_mm<72>(54.1), to_mm<72>(78.08), "Scale", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(115.27), to_mm<72>(61.62), "Spread", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(176.96), to_mm<72>(78.07), "Pitch", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(32.72), to_mm<72>(144.14), "Balance", "", 0, 0, 1, 0.0f},
		DaviesLargeKnob{to_mm<72>(115.56), to_mm<72>(140.93), "Root", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(198.23), to_mm<72>(144.14), "Cross FM", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(61.77), to_mm<72>(208.21), "Twist", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(115.49), to_mm<72>(207.86), "Detune", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(168.87), to_mm<72>(208.21), "Warp", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(21.88), to_mm<72>(262.78), "Pitch Jack", ""},
		AnalogJackInput4ms{to_mm<72>(59.42), to_mm<72>(275.86), "Scale Jack", ""},
		AnalogJackInput4ms{to_mm<72>(96.88), to_mm<72>(262.78), "Spread Jack", ""},
		AnalogJackInput4ms{to_mm<72>(134.28), to_mm<72>(262.78), "Cross FM Jack", ""},
		GateJackInput4ms{to_mm<72>(171.75), to_mm<72>(275.86), "Learn Jack", ""},
		AnalogJackInput4ms{to_mm<72>(21.88), to_mm<72>(305.91), "Root Jack", ""},
		AnalogJackInput4ms{to_mm<72>(59.42), to_mm<72>(319.0), "Balance Jack", ""},
		AnalogJackInput4ms{to_mm<72>(96.88), to_mm<72>(305.93), "Twist Jack", ""},
		AnalogJackInput4ms{to_mm<72>(134.28), to_mm<72>(305.93), "Warp Jack", ""},
		GateJackInput4ms{to_mm<72>(171.75), to_mm<72>(319.03), "Freeze Jack", ""},
		AnalogJackOutput4ms{to_mm<72>(209.12), to_mm<72>(262.78), "Out A", ""},
		AnalogJackOutput4ms{to_mm<72>(209.12), to_mm<72>(305.91), "Out B", ""},
		Toggle3pos{to_mm<72>(16.93), to_mm<72>(103.025), "Scale Switch", ""},
		Toggle3pos{to_mm<72>(214.23), to_mm<72>(102.945), "Cross FM Switch", ""},
		Toggle3pos{to_mm<72>(16.93), to_mm<72>(215.065), "Twist Switch", ""},
		Toggle3pos{to_mm<72>(214.23), to_mm<72>(201.725), "Warp Switch", ""},
		MomentaryButtonWhiteLight{to_mm<72>(21.63), to_mm<72>(42.53), "Learn", ""},
		MomentaryButtonWhiteLight{to_mm<72>(209.56), to_mm<72>(42.53), "Freeze", ""},
	}};

	enum class Elem {
		ScaleKnob,
		SpreadKnob,
		PitchKnob,
		BalanceKnob,
		RootKnob,
		CrossFmKnob,
		TwistKnob,
		DetuneKnob,
		WarpKnob,
		PitchJackIn,
		ScaleJackIn,
		SpreadJackIn,
		CrossFmJackIn,
		LearnJackIn,
		RootJackIn,
		BalanceJackIn,
		TwistJackIn,
		WarpJackIn,
		FreezeJackIn,
		OutAOut,
		OutBOut,
		ScaleSwitchSwitch,
		CrossFmSwitchSwitch,
		TwistSwitchSwitch,
		WarpSwitchSwitch,
		LearnButton,
		FreezeButton,
	};

	// Legacy naming (safe to remove once CoreModule is converted

	enum {
		KnobScale = 0,
		KnobSpread = 1,
		KnobPitch = 2,
		KnobBalance = 3,
		KnobRoot = 4,
		KnobCross_Fm = 5,
		KnobTwist = 6,
		KnobDetune = 7,
		KnobWarp = 8,
	};

	enum {
		SwitchScale_Switch = 0,
		SwitchCross_Fm_Switch = 1,
		SwitchTwist_Switch = 2,
		SwitchWarp_Switch = 3,
		SwitchLearn = 4,
		SwitchFreeze = 5,
	};

	enum {
		InputPitch_Jack = 0,
		InputScale_Jack = 1,
		InputSpread_Jack = 2,
		InputCross_Fm_Jack = 3,
		InputLearn_Jack = 4,
		InputRoot_Jack = 5,
		InputBalance_Jack = 6,
		InputTwist_Jack = 7,
		InputWarp_Jack = 8,
		InputFreeze_Jack = 9,
	};

	enum {
		OutputOut_A = 0,
		OutputOut_B = 1,
	};

	static constexpr int NumAltParams = 4;

	enum {
		AltCrossfade_Time = 0,
		AltStereo_Split = 1,
		AltNum_Oscs = 2,
		AltFreeze_Split = 3,
	};

	// static constexpr std::array<AltParamDef, NumAltParams> AltParams{{
	// 	{
	// 		.id = AltCrossfade_Time,
	// 		.short_name = "Crossfade Smoothness",
	// 		.min_val = 0.f,
	// 		.max_val = 1.f,
	// 		.default_val = 0.5f,
	// 		.attached_to_param_id = KnobBalance,
	// 		.attached_to = AltParamDef::AttachedTo::Knob,
	// 		.control_type = AltParamDef::Range::Continuous,
	// 	},
	// 	{
	// 		.id = AltStereo_Split,
	// 		.short_name = "Stereo Split",
	// 		.min_val = 0.f,
	// 		.max_val = 2.f,
	// 		.default_val = 1.f,
	// 		.attached_to_param_id = KnobTwist,
	// 		.attached_to = AltParamDef::AttachedTo::Knob,
	// 		.control_type = AltParamDef::Range::Integer,
	// 	},
	// 	{
	// 		.id = AltNum_Oscs,
	// 		.short_name = "Num Oscillators",
	// 		.min_val = 0.f,
	// 		.max_val = 16.f,
	// 		.default_val = 16.f,
	// 		.attached_to_param_id = KnobSpread,
	// 		.attached_to = AltParamDef::AttachedTo::Knob,
	// 		.control_type = AltParamDef::Range::Integer,
	// 	},
	// 	{
	// 		.id = AltFreeze_Split,
	// 		.short_name = "Freeze Split",
	// 		.min_val = 0.f,
	// 		.max_val = 2.f,
	// 		.default_val = 1.f,
	// 		.attached_to_param_id = KnobWarp,
	// 		.attached_to = AltParamDef::AttachedTo::Knob,
	// 		.control_type = AltParamDef::Range::Integer,
	// 	},
	// }};
};

} // namespace MetaModule
