#pragma once
#include "CoreModules/elements.hh"
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

namespace MetaModule
{

struct BraidsInfo : ElementInfoBase {
	// Module info: written by hand
	static constexpr std::string_view slug{"Brainds"};
	static constexpr std::string_view description{"Macro Oscillator"};
	static constexpr uint32_t width_hp = 16; //CHECK!
	static constexpr std::string_view svg_filename{"res/modules/AudibleInstruments/Braids.svg"};

	// Regex to convert addParam(...) or addInput/Output() to Elements:
	// s/add\w\+(create\w\+<\(.*\)>(Vec(\(\d\+\), \(\d\+\)), .*::\(.*\)_\(\w\+\).*/\t\t\1{\2, \3, "\4", "", \4_\5},/
	// Then manually add the names from Module::configParam()

	static constexpr std::array<Element, 14> Elements{{
		Rogan2SGray{176, 59, "Model", "", SHAPE_PARAM},
		Rogan2PSWhite{19, 138, "Fine", "Fine Freq", FINE_PARAM},
		Rogan2PSWhite{97, 138, "Coarse", "Coarse Freq", COARSE_PARAM},
		Rogan2PSWhite{176, 138, "FM", "", FM_PARAM},
		Rogan2PSGreen{19, 217, "Timbre", "", TIMBRE_PARAM},
		Rogan2PSGreen{97, 217, "Modulation", "", MODULATION_PARAM},
		Rogan2PSRed{176, 217, "Color", "", COLOR_PARAM},
		PJ301MPort{10, 316, "Trigger", "", TRIG_INPUT},
		PJ301MPort{47, 316, "Pitch", "Pitch (1V/oct)", PITCH_INPUT},
		PJ301MPort{84, 316, "FM", "", FM_INPUT},
		PJ301MPort{122, 316, "Timbre", "", TIMBRE_INPUT},
		PJ301MPort{160, 316, "Color", "", COLOR_INPUT},
		PJ301MPort{205, 316, "Out", "", OUT_OUTPUT},
		BraidsDisplay148x56{14, 53, "", ""},
	}}; // namespace MetaModule
};
} // namespace MetaModule
