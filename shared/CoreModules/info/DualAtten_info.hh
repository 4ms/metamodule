#pragma once
#include "CoreModules/elements.hh"
#include <array>

namespace MetaModule
{

struct BefacoDualAttenInfo {
	// Module info: written by hand
	static constexpr std::string_view slug{"BEFACOATTEN"};
	static constexpr std::string_view description{"Dual Attenuator"};
	static constexpr uint32_t width_hp = 8; //FIXME: CHECK THIS
	static constexpr std::string_view svg_filename{"res/modules/befaco/DualAtenuverter.svg"};

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

	// Convert addParam(...) or addInput/Output() to Element:
	// s/add\w\+(create\w\+<\(.*\)>(Vec(\(\d\+\), \(\d\+\)), .*::\(.*\)_\(\w\+\).*/\t\t\1{\2, \3, "\4", "", \4_\5},/
	// Then manually add the names from Module::configParam()
	static constexpr std::array<KnobElement, 4> knobs{{
		Davies1900hWhiteKnob{20, 33, "Ch 1 gain", "", ATEN1_PARAM},
		Davies1900hRedKnob{20, 91, "Ch 1 offset", "", OFFSET1_PARAM},
		Davies1900hWhiteKnob{20, 201, "Ch 2 gain", "", ATEN2_PARAM},
		Davies1900hRedKnob{20, 260, "Ch 2 offset", "", OFFSET2_PARAM},
	}};

	static constexpr std::array<KnobElement, 0> switches{};

	static constexpr std::array<InJackElement, 2> injacks{{
		BefacoInputPort{7, 152, "IN1", "", IN1_INPUT},
		BefacoInputPort{7, 319, "IN2", "", IN2_INPUT},
	}};

	static constexpr std::array<OutJackElement, 2> outjacks{{
		BefacoOutputPort{43, 152, "OUT1", "", OUT1_OUTPUT},
		BefacoOutputPort{43, 319, "OUT2", "", OUT2_OUTPUT},
	}};

	static constexpr std::array<LightElement, 2> lights{{
		MediumLight<RedGreenBlueLight>{33, 143, "OUT1", "", OUT1_LIGHT},
		MediumLight<RedGreenBlueLight>{33, 311, "OUT2", "", OUT2_LIGHT},
	}};

	// Cpnvert the elements arrays to named elements
	// s/\v\s+(.*)\{(\d+), (\d+), "(\w+)", ""},/\tstatic constexpr auto \4 = std::get<\1>(elements[0]);/
	// Then, change elements[0] to correct name/number
	// Then, fix any duplicate names
	static constexpr auto ATEN1 = std::get<Davies1900hWhiteKnob>(knobs[0]);
	static constexpr auto OFFSET1 = std::get<Davies1900hRedKnob>(knobs[1]);
	static constexpr auto ATEN2 = std::get<Davies1900hWhiteKnob>(knobs[2]);
	static constexpr auto OFFSET2 = std::get<Davies1900hRedKnob>(knobs[3]);
	static constexpr auto IN1 = std::get<BefacoInputPort>(injacks[0]);
	static constexpr auto OUT1 = std::get<BefacoOutputPort>(outjacks[0]);
	static constexpr auto IN2 = std::get<BefacoInputPort>(injacks[1]);
	static constexpr auto OUT2 = std::get<BefacoOutputPort>(outjacks[1]);
	static constexpr auto OUT1_LED = std::get<MediumLight<RedGreenBlueLight>>(lights[0]);
	static constexpr auto OUT2_LED = std::get<MediumLight<RedGreenBlueLight>>(lights[1]);
};
} // namespace MetaModule
