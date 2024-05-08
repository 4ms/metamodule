#pragma once
#include "../../shared/CoreModules/4ms/4ms_element_state_conversions.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct RingsInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Rings"};
	static constexpr std::string_view description{"Resonance Module"};
	static constexpr uint32_t width_hp = 14;
	static constexpr std::string_view svg_filename{"res/modules/Rings_artwork.svg"};

	using enum Coords;

	static constexpr std::array<Element, 22> Elements{{
		Toggle3posHoriz{{to_mm<72>(21.19), to_mm<72>(45.705), Center, "Polyphony Select Switch", ""}, {"1", "2", "4"}},
		Toggle3posHoriz{{to_mm<72>(179.64), to_mm<72>(45.705), Center, "Resonator Mode Switch", ""},
						{"Modal", "Symp", "Mod"}},
		DaviesLargeKnob{{to_mm<72>(53.64), to_mm<72>(93.0), Center, "Frequency", ""}},
		DaviesLargeKnob{{to_mm<72>(147.2), to_mm<72>(93.0), Center, "Structure", ""}},
		Davies1900hBlackKnob{{to_mm<72>(32.9), to_mm<72>(171.86), Center, "Brightness", ""}},
		Davies1900hBlackKnob{{to_mm<72>(100.39), to_mm<72>(171.86), Center, "Damping", ""}},
		Davies1900hBlackKnob{{to_mm<72>(167.88), to_mm<72>(171.86), Center, "Position", ""}},
		Knob9mm{{to_mm<72>(26.67), to_mm<72>(228.56), Center, "Br Atten", ""}},
		Knob9mm{{to_mm<72>(63.54), to_mm<72>(228.56), Center, "Frq Atten", ""}},
		Knob9mm{{to_mm<72>(100.4), to_mm<72>(228.56), Center, "Dmp Atten", ""}},
		Knob9mm{{to_mm<72>(137.27), to_mm<72>(228.56), Center, "Str Atten", ""}},
		Knob9mm{{to_mm<72>(174.13), to_mm<72>(228.56), Center, "Pos Atten", ""}},
		AnalogJackInput4ms{{to_mm<72>(26.66), to_mm<72>(273.49), Center, "Brightness CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(63.53), to_mm<72>(273.49), Center, "Frequency CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(100.39), to_mm<72>(273.49), Center, "Damping CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(137.26), to_mm<72>(273.49), Center, "Structure CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(174.12), to_mm<72>(273.49), Center, "Position CV", ""}},
		AnalogJackInput4ms{{to_mm<72>(26.66), to_mm<72>(314.88), Center, "Strum", ""}},
		AnalogJackInput4ms{{to_mm<72>(63.53), to_mm<72>(314.88), Center, "V/OCT", ""}},
		AnalogJackInput4ms{{to_mm<72>(100.39), to_mm<72>(314.88), Center, "IN", ""}},
		AnalogJackOutput4ms{{to_mm<72>(137.26), to_mm<72>(314.88), Center, "Odd", ""}},
		AnalogJackOutput4ms{{to_mm<72>(174.12), to_mm<72>(314.88), Center, "Even", ""}},
	}};

	enum class Elem {
		PolyphonySelectSwitch,
		ResonatorModeSwitch,
		FrequencyKnob,
		StructureKnob,
		BrightnessKnob,
		DampingKnob,
		PositionKnob,
		BrAttenKnob,
		FrqAttenKnob,
		DmpAttenKnob,
		StrAttenKnob,
		PosAttenKnob,
		BrightnessCvIn,
		FrequencyCvIn,
		DampingCvIn,
		StructureCvIn,
		PositionCvIn,
		StrumIn,
		V_OctIn,
		In,
		OddOut,
		EvenOut,
	};

	// Legacy naming (safe to remove once all legacy 4ms CoreModules are converted)

	enum {
		KnobFrequency,
		KnobStructure,
		KnobBrightness,
		KnobDamping,
		KnobPosition,
		KnobBr_Atten,
		KnobFrq_Atten,
		KnobDmp_Atten,
		KnobStr_Atten,
		KnobPos_Atten,
		NumKnobs,
	};

	enum {
		SwitchPolyphony_Select_Switch,
		SwitchResonator_Mode_Switch,
		NumSwitches,
	};

	enum {
		InputBrightness_Cv,
		InputFrequency_Cv,
		InputDamping_Cv,
		InputStructure_Cv,
		InputPosition_Cv,
		InputStrum,
		InputV_Oct,
		InputIn,
		NumInJacks,
	};

	enum {
		OutputOdd,
		OutputEven,
		NumOutJacks,
	};
};
} // namespace MetaModule
