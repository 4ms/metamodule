#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>
#include <string_view>

enum ParamIds { OCTAVE_PARAM, TUNE_PARAM, PWM_PARAM, NUM_PARAMS };
enum InputIds { PITCH1_INPUT, PITCH2_INPUT, FM_INPUT, SYNC_INPUT, PWM_INPUT, NUM_INPUTS };
enum OutputIds { TRI_OUTPUT, SINE_OUTPUT, EVEN_OUTPUT, SAW_OUTPUT, SQUARE_OUTPUT, NUM_OUTPUTS };

namespace MetaModule
{

struct EvenVCOInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"EvenVCO"};
	static constexpr std::string_view description{"Befaco EvenVCO"};
	static constexpr uint32_t width_hp = 8;
	static constexpr std::string_view svg_filename{"res/modules/Befaco/EvenVCO.svg"};

	static constexpr std::array<Element, 13> Elements{{
		BefacoBigKnob{{{{to_mm(22), to_mm(32), "Octave", "", OCTAVE_PARAM}, -5, 4}}}, //snap enabled
		BefacoTinyKnob{{{{to_mm(73), to_mm(131), "Tune", "", TUNE_PARAM}, -7, 7}}},
		Davies1900hRedKnob{{{{to_mm(16), to_mm(230), "Pulse Width", "", PWM_PARAM}, -1, 1}}},

		BefacoInputPort{to_mm(8), to_mm(120), "Pitch 1", "", PITCH1_INPUT},
		BefacoInputPort{to_mm(19), to_mm(157), "Pitch 2", "", PITCH2_INPUT},
		BefacoInputPort{to_mm(48), to_mm(183), "FM", "", FM_INPUT},
		BefacoInputPort{to_mm(86), to_mm(189), "Sync", "", SYNC_INPUT},

		BefacoInputPort{to_mm(72), to_mm(236), "PWM", "", PWM_INPUT},

		BefacoOutputPort{to_mm(10), to_mm(283), "Triangle", "", TRI_OUTPUT},
		BefacoOutputPort{to_mm(87), to_mm(283), "sine", "", SINE_OUTPUT},
		BefacoOutputPort{to_mm(48), to_mm(306), "Even", "", EVEN_OUTPUT},
		BefacoOutputPort{to_mm(10), to_mm(327), "Sawtooth", "", SAW_OUTPUT},
		BefacoOutputPort{to_mm(87), to_mm(327), "Square", "", SQUARE_OUTPUT},
	}};
};
}; // namespace MetaModule
