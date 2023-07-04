#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule
{
struct DjembeInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Djembe"};
	static constexpr std::string_view description{"Djembe Drum Voice"};
	static constexpr uint32_t width_hp = 8;
	static constexpr bool uses_center_coords = true;
	static constexpr std::string_view svg_filename{"res/modules/Djembe-artwork.svg"};

	static constexpr std::array<Element, 10> Elements{{
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(57.97), "Pitch", "", 0, 0, 1, 0.25f},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(57.97), "Sharpness", "", 0, 0, 1, 0.0f},
		Davies1900hBlackKnob{to_mm<72>(31.96), to_mm<72>(119.21), "Hit", "", 0, 0, 1, 0.5f},
		Davies1900hBlackKnob{to_mm<72>(83.49), to_mm<72>(119.21), "Strike Amt", "", 0, 0, 1, 0.5f},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(214.66), "Pitch CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.32), to_mm<72>(214.66), "Sharp CV", ""},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(263.38), "Hit CV", ""},
		AnalogJackInput4ms{to_mm<72>(83.32), to_mm<72>(263.38), "Strike CV", ""},
		AnalogJackInput4ms{to_mm<72>(32.13), to_mm<72>(312.1), "Trigger", ""},
		AnalogJackOutput4ms{to_mm<72>(83.32), to_mm<72>(312.1), "Out", ""},
	}};

	enum class Elem {
		PitchKnob,
		SharpnessKnob,
		HitKnob,
		StrikeAmtKnob,
		PitchCvIn,
		SharpCvIn,
		HitCvIn,
		StrikeCvIn,
		TriggerIn,
		OutOut,
	};
};
} // namespace MetaModule
