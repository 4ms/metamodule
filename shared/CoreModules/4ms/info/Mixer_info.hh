#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct MixerInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Mixer4"};
	static constexpr std::string_view description{"4 Ch. Mixer"};
	static constexpr uint32_t width_hp = 10;
	static constexpr bool uses_center_coords = true;
	static constexpr std::string_view svg_filename{"res/modules/Mixer-artwork.svg"};

	static constexpr std::array<Element, 10> Elements{{
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(46.42), "Level 1", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(46.42), "Level 2", "", 0, 0, 1, 0.875f},
		Davies1900hBlackKnob{to_mm<72>(37.85), to_mm<72>(104.62), "Level 3", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(106.4), to_mm<72>(104.62), "Level 4", "", 0, 0, 1, 0.875f},
		AnalogJackInput4ms{to_mm<72>(29.94), to_mm<72>(272.23), "In 1", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(272.23), "In 2", ""},
		AnalogJackInput4ms{to_mm<72>(115.17), to_mm<72>(272.23), "In 3", ""},
		AnalogJackInput4ms{to_mm<72>(72.13), to_mm<72>(313.84), "In 4", ""},
		AnalogJackOutput4ms{to_mm<72>(29.94), to_mm<72>(313.84), "Inv", ""},
		AnalogJackOutput4ms{to_mm<72>(115.17), to_mm<72>(313.84), "Out", ""},
	}};

	enum class Elem {
		Level1Knob,
		Level2Knob,
		Level3Knob,
		Level4Knob,
		In1In,
		In2In,
		In3In,
		In4In,
		InvOut,
		Out,
	};

	// Legacy naming (safe to remove once CoreModule is converted

	enum {
		KnobLevel_1 = 0,
		KnobLevel_2 = 1,
		KnobLevel_3 = 2,
		KnobLevel_4 = 3,
		NumKnobs,
	};

	enum {
		InputIn_1 = 0,
		InputIn_2 = 1,
		InputIn_3 = 2,
		InputIn_4 = 3,
		NumInJacks,
	};

	enum {
		OutputInv = 0,
		OutputOut = 1,
		NumOutJacks,
	};
};
} // namespace MetaModule
