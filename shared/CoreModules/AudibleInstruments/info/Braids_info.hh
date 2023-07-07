#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/element_info.hh"
#include <array>

enum ParamIds {
	FINE_PARAM,
	COARSE_PARAM,
	FM_PARAM,
	TIMBRE_PARAM,
	MODULATION_PARAM,
	COLOR_PARAM,
	SHAPE_PARAM,
	NUM_PARAMS
};
enum InputIds { TRIG_INPUT, PITCH_INPUT, FM_INPUT, TIMBRE_INPUT, COLOR_INPUT, NUM_INPUTS };
enum OutputIds { OUT_OUTPUT, NUM_OUTPUTS };
enum LightIds { NUM_LIGHTS };

namespace MetaModule
{

struct BraidsInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Braids"};
	static constexpr std::string_view description{"Macro Oscillator"};
	static constexpr uint32_t width_hp = 16;
	static constexpr std::string_view svg_filename{"res/modules/AudibleInstruments/Braids.svg"};

	static constexpr std::array<Element, 14> Elements{{
		Rogan2SGray{{{{to_mm(176), to_mm(59), "Model", "", SHAPE_PARAM}, 0.f, 1.f, 0.f}}},
		Rogan2PSWhite{{{{to_mm(19), to_mm(138), "Fine", "Fine Freq", FINE_PARAM}, -1.f, 1.f, 0.f}}},
		Rogan2PSWhite{{{{to_mm(97), to_mm(138), "Coarse", "Coarse Freq", COARSE_PARAM}, -5.f, 3.f, -1.f}}},
		Rogan2PSWhite{{{{to_mm(176), to_mm(138), "FM", "", FM_PARAM}, -1.f, 1.f, 0.f}}},
		Rogan2PSGreen{{{{to_mm(19), to_mm(217), "Timbre", "", TIMBRE_PARAM}, 0.f, 1.f, 0.5f}}},
		Rogan2PSGreen{{{{to_mm(97), to_mm(217), "Modulation", "", MODULATION_PARAM}, -1.f, 1.f, 0.f}}},
		Rogan2PSRed{{{{to_mm(176), to_mm(217), "Color", "", COLOR_PARAM}, 0.f, 1.f, 0.5f}}},
		PJ301MPortIn{to_mm(10), to_mm(316), "Trigger", "", TRIG_INPUT},
		PJ301MPortIn{to_mm(47), to_mm(316), "Pitch", "Pitch (1V/oct)", PITCH_INPUT},
		PJ301MPortIn{to_mm(84), to_mm(316), "FM", "", FM_INPUT},
		PJ301MPortIn{to_mm(122), to_mm(316), "Timbre", "", TIMBRE_INPUT},
		PJ301MPortIn{to_mm(160), to_mm(316), "Color", "", COLOR_INPUT},
		PJ301MPortOut{to_mm(205), to_mm(316), "Out", "", OUT_OUTPUT},
		BraidsDisplay148x56{to_mm(14), to_mm(53), "", ""},
	}};

	// FAILS:
	// static_assert(ElementCount::get_indices<BraidsInfo>(std::get<Rogan2SGray>(Elements[0])).value().param_idx == SHAPE_PARAM);
};
} // namespace MetaModule
