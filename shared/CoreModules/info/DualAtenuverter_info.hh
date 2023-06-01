#pragma once
#include "CoreModules/elements.hh"
#include <array>

// TODO: get these out of global namespace
// Enums: Copied from VCV Module:
enum ParamIds { ATEN1_PARAM, OFFSET1_PARAM, ATEN2_PARAM, OFFSET2_PARAM, NUM_PARAMS };
enum InputIds { IN1_INPUT, IN2_INPUT, NUM_INPUTS };
enum OutputIds { OUT1_OUTPUT, OUT2_OUTPUT, NUM_OUTPUTS };
// enum LightIds { ENUMS(OUT1_LIGHT, 3), ENUMS(OUT2_LIGHT, 3), NUM_LIGHTS };
enum LightIds {
	OUT1_LIGHT,
	OUT1_LIGHT_LAST = OUT1_LIGHT + 2,
	OUT2_LIGHT,
	OUT2_LIGHT2_LAST = OUT2_LIGHT + 2,
	NUM_LIGHTS
};

namespace MetaModule
{

struct DualAtenuverterInfo : ElementInfoBase {
	// Module info: written by hand
	static constexpr std::string_view slug{"DualAtenuverter"};
	static constexpr std::string_view description{"Befaco Dual Attenuvertor"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::string_view svg_filename{"res/modules/Befaco/DualAtenuverter.svg"};

	// Regex to convert addParam(...) or addInput/Output() to *Elements:
	// s/add\w\+(create\w\+<\(.*\)>(Vec(\(\d\+\), \(\d\+\)), .*::\(.*\)_\(\w\+\).*/\t\t\1{\2, \3, "\4", "", \4_\5},/
	// Then manually add the names from Module::configParam()
	// and manually split into arrays for each type of element

	static constexpr std::array<Element, 10> Elements{{
		Davies1900hWhiteKnob{20, 33, "Ch 1 gain", "", ATEN1_PARAM},
		Davies1900hRedKnob{20, 91, "Ch 1 offset", "", OFFSET1_PARAM},
		Davies1900hWhiteKnob{20, 201, "Ch 2 gain", "", ATEN2_PARAM},
		Davies1900hRedKnob{20, 260, "Ch 2 offset", "", OFFSET2_PARAM},
		BefacoInputPort{7, 152, "IN1", "", IN1_INPUT},
		BefacoInputPort{7, 319, "IN2", "", IN2_INPUT},
		BefacoOutputPort{43, 152, "OUT1", "", OUT1_OUTPUT},
		BefacoOutputPort{43, 319, "OUT2", "", OUT2_OUTPUT},
		MediumLight<RedGreenBlueLight>{33, 143, "OUT1", "", OUT1_LIGHT},
		MediumLight<RedGreenBlueLight>{33, 311, "OUT2", "", OUT2_LIGHT},
	}};
};
} // namespace MetaModule
