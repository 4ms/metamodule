#pragma once
#include "CoreModules/elements/4ms_elements.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct HubMediumInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"HubMedium"};
	static constexpr std::string_view description{"MetaModule"};
	static constexpr uint32_t width_hp = 26;
	static constexpr std::string_view svg_filename{"res/modules/HubMedium-artwork.svg"};

	using enum Coords;
	static constexpr std::array<Element, 29> Elements{{
		Davies1900hBlackKnob{{to_mm<72>(32.89), to_mm<72>(213.17), Center, "A", ""}},
		Davies1900hBlackKnob{{to_mm<72>(92.87), to_mm<72>(201.73), Center, "B", ""}},
		Davies1900hBlackKnob{{to_mm<72>(153.77), to_mm<72>(213.17), Center, "C", ""}},
		Davies1900hBlackKnob{{to_mm<72>(218.71), to_mm<72>(213.17), Center, "D", ""}},
		Davies1900hBlackKnob{{to_mm<72>(279.38), to_mm<72>(201.83), Center, "E", ""}},
		Davies1900hBlackKnob{{to_mm<72>(340.01), to_mm<72>(213.17), Center, "F", ""}},
		Knob9mm{{to_mm<72>(26.58), to_mm<72>(61.85), Center, "u", ""}},
		Knob9mm{{to_mm<72>(61.07), to_mm<72>(110.02), Center, "v", ""}},
		Knob9mm{{to_mm<72>(26.6), to_mm<72>(157.86), Center, "w", ""}},
		Knob9mm{{to_mm<72>(345.28), to_mm<72>(91.46), Center, "x", ""}},
		Knob9mm{{to_mm<72>(302.03), to_mm<72>(123.31), Center, "y", ""}},
		Knob9mm{{to_mm<72>(345.31), to_mm<72>(157.07), Center, "z", ""}},
		AnalogJackInput4ms{{to_mm<72>(208.16), to_mm<72>(323.62), Center, "out1", ""}},
		AnalogJackInput4ms{{to_mm<72>(251.6), to_mm<72>(323.86), Center, "out2", ""}},
		AnalogJackInput4ms{{to_mm<72>(294.05), to_mm<72>(323.62), Center, "out3", ""}},
		AnalogJackInput4ms{{to_mm<72>(337.49), to_mm<72>(323.62), Center, "out4", ""}},
		AnalogJackInput4ms{{to_mm<72>(221.02), to_mm<72>(282.17), Center, "out5", ""}},
		AnalogJackInput4ms{{to_mm<72>(264.39), to_mm<72>(282.17), Center, "out6", ""}},
		AnalogJackInput4ms{{to_mm<72>(307.65), to_mm<72>(281.86), Center, "out7", ""}},
		AnalogJackInput4ms{{to_mm<72>(351.09), to_mm<72>(281.86), Center, "out8", ""}},
		AnalogJackOutput4ms{{to_mm<72>(35.03), to_mm<72>(323.62), Center, "in1", ""}},
		AnalogJackOutput4ms{{to_mm<72>(78.54), to_mm<72>(323.62), Center, "in2", ""}},
		AnalogJackOutput4ms{{to_mm<72>(121.2), to_mm<72>(323.86), Center, "in3", ""}},
		AnalogJackOutput4ms{{to_mm<72>(164.86), to_mm<72>(323.86), Center, "in4", ""}},
		AnalogJackOutput4ms{{to_mm<72>(108.32), to_mm<72>(282.34), Center, "in5", ""}},
		AnalogJackOutput4ms{{to_mm<72>(150.84), to_mm<72>(282.34), Center, "in6", ""}},
		GateJackOutput4ms{{to_mm<72>(21.74), to_mm<72>(274.18), Center, "gatein1", ""}},
		GateJackOutput4ms{{to_mm<72>(65.25), to_mm<72>(274.2), Center, "gatein2", ""}},
		LatchingButtonMonoLight{{to_mm<72>(344.18), to_mm<72>(38.57), Center, "SavePatch", ""}},
	}};

	enum class Elem {
		AKnob,
		BKnob,
		CKnob,
		DKnob,
		EKnob,
		FKnob,
		UKnob,
		VKnob,
		WKnob,
		XKnob,
		YKnob,
		ZKnob,
		Out1In,
		Out2In,
		Out3In,
		Out4In,
		Out5In,
		Out6In,
		Out7In,
		Out8In,
		In1Out,
		In2Out,
		In3Out,
		In4Out,
		In5Out,
		In6Out,
		Gatein1Out,
		Gatein2Out,
		SavepatchButton,
	};

	// Legacy naming (safe to remove once CoreModule is converted

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
		NumKnobs,
	};

	enum {
		SwitchSavepatch = 0,
		NumSwitches,
	};

	enum {
		InputOut1 = 0,
		InputOut2 = 1,
		InputOut3 = 2,
		InputOut4 = 3,
		InputOut5 = 4,
		InputOut6 = 5,
		InputOut7 = 6,
		InputOut8 = 7,
		NumInJacks,
	};

	enum {
		OutputIn1 = 0,
		OutputIn2 = 1,
		OutputIn3 = 2,
		OutputIn4 = 3,
		OutputIn5 = 4,
		OutputIn6 = 5,
		OutputGatein1 = 6,
		OutputGatein2 = 7,
		NumOutJacks,
	};
};
} // namespace MetaModule
