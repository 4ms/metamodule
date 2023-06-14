#pragma once
#include "CoreModules/element_info.hh"
#include <array>

// TODO: get these out of global namespace
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

struct BraidsInfo : ElementInfoBase {
	static constexpr std::string_view slug{"Braids"};
	static constexpr std::string_view description{"Macro Oscillator"};
	static constexpr uint32_t width_hp = 16;
	static constexpr std::string_view svg_filename{"res/modules/AudibleInstruments/Braids.svg"};

	static constexpr std::array<Element, 14> Elements{{
		Rogan2SGray{to_mm(176), to_mm(59), "Model", "", SHAPE_PARAM},
		Rogan2PSWhite{to_mm(19), to_mm(138), "Fine", "Fine Freq", FINE_PARAM},
		Rogan2PSWhite{to_mm(97), to_mm(138), "Coarse", "Coarse Freq", COARSE_PARAM},
		Rogan2PSWhite{to_mm(176), to_mm(138), "FM", "", FM_PARAM},
		Rogan2PSGreen{to_mm(19), to_mm(217), "Timbre", "", TIMBRE_PARAM},
		Rogan2PSGreen{to_mm(97), to_mm(217), "Modulation", "", MODULATION_PARAM},
		Rogan2PSRed{to_mm(176), to_mm(217), "Color", "", COLOR_PARAM},
		PJ301MPort{to_mm(10), to_mm(316), "Trigger", "", TRIG_INPUT},
		PJ301MPort{to_mm(47), to_mm(316), "Pitch", "Pitch (1V/oct)", PITCH_INPUT},
		PJ301MPort{to_mm(84), to_mm(316), "FM", "", FM_INPUT},
		PJ301MPort{to_mm(122), to_mm(316), "Timbre", "", TIMBRE_INPUT},
		PJ301MPort{to_mm(160), to_mm(316), "Color", "", COLOR_INPUT},
		PJ301MPort{to_mm(205), to_mm(316), "Out", "", OUT_OUTPUT},
		BraidsDisplay148x56{to_mm(14), to_mm(53), "", ""},
	}};
};
} // namespace MetaModule
