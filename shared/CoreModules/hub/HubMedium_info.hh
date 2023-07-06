#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct HubMediumInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"HubMedium"};
	static constexpr std::string_view description{"MetaModule"};
	static constexpr uint32_t width_hp = 26;
	static constexpr bool uses_center_coords = true;
	static constexpr std::string_view svg_filename{"res/modules/HubMedium-artwork.svg"};

	static constexpr std::array<Element, 29> Elements{{
		Davies1900hBlackKnob{to_mm<72>(32.89), to_mm<72>(213.17), "A", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(92.87), to_mm<72>(201.73), "B", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(153.77), to_mm<72>(213.17), "C", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(218.71), to_mm<72>(213.17), "D", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(279.38), to_mm<72>(201.83), "E", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(340.01), to_mm<72>(213.17), "F", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(26.58), to_mm<72>(61.85), "u", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(61.07), to_mm<72>(110.02), "v", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(26.6), to_mm<72>(157.86), "w", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(345.28), to_mm<72>(91.46), "x", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(302.03), to_mm<72>(123.31), "y", "", 0, 0, 1, 0.0f},
		Knob9mm{to_mm<72>(345.31), to_mm<72>(157.07), "z", "", 0, 0, 1, 0.0f},
		AnalogJackInput4ms{to_mm<72>(35.03), to_mm<72>(323.62), "in1", ""},
		AnalogJackInput4ms{to_mm<72>(78.54), to_mm<72>(323.62), "in2", ""},
		AnalogJackInput4ms{to_mm<72>(121.2), to_mm<72>(323.86), "in3", ""},
		AnalogJackInput4ms{to_mm<72>(164.86), to_mm<72>(323.86), "in4", ""},
		AnalogJackInput4ms{to_mm<72>(108.32), to_mm<72>(282.34), "in5", ""},
		AnalogJackInput4ms{to_mm<72>(150.84), to_mm<72>(282.34), "in6", ""},
		GateJackInput4ms{to_mm<72>(21.74), to_mm<72>(274.18), "gatein1", ""},
		GateJackInput4ms{to_mm<72>(65.25), to_mm<72>(274.2), "gatein2", ""},
		AnalogJackOutput4ms{to_mm<72>(208.16), to_mm<72>(323.62), "out1", ""},
		AnalogJackOutput4ms{to_mm<72>(251.6), to_mm<72>(323.86), "out2", ""},
		AnalogJackOutput4ms{to_mm<72>(294.05), to_mm<72>(323.62), "out3", ""},
		AnalogJackOutput4ms{to_mm<72>(337.49), to_mm<72>(323.62), "out4", ""},
		AnalogJackOutput4ms{to_mm<72>(221.02), to_mm<72>(282.17), "out5", ""},
		AnalogJackOutput4ms{to_mm<72>(264.39), to_mm<72>(282.17), "out6", ""},
		AnalogJackOutput4ms{to_mm<72>(307.65), to_mm<72>(281.86), "out7", ""},
		AnalogJackOutput4ms{to_mm<72>(351.09), to_mm<72>(281.86), "out8", ""},
		LatchingButtonMonoLight{to_mm<72>(352.2), to_mm<72>(43.24), "SavePatch", ""},
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
		In1In,
		In2In,
		In3In,
		In4In,
		In5In,
		In6In,
		Gatein1In,
		Gatein2In,
		Out1Out,
		Out2Out,
		Out3Out,
		Out4Out,
		Out5Out,
		Out6Out,
		Out7Out,
		Out8Out,
		SavepatchButton,
	};
};
} // namespace MetaModule
