#pragma once
#include "CoreModules/elements.hh"
#include <array>

// TODO: get these out of global namespace
// Enums copied from VCV Module:
enum ParamIds { ATEN1_PARAM, OFFSET1_PARAM, ATEN2_PARAM, OFFSET2_PARAM, NUM_PARAMS };
enum InputIds { IN1_INPUT, IN2_INPUT, NUM_INPUTS };
enum OutputIds { OUT1_OUTPUT, OUT2_OUTPUT, NUM_OUTPUTS };
enum LightIds { ENUMS(OUT1_LIGHT, 3), ENUMS(OUT2_LIGHT, 3), NUM_LIGHTS };

namespace MetaModule
{

struct DualAtenuverterInfo : ElementInfoBase {
	// Module info: written by hand
	static constexpr std::string_view slug{"DualAtenuverter"};
	static constexpr std::string_view description{"Befaco Dual Attenuvertor"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::string_view svg_filename{"res/modules/Befaco/DualAtenuverter.svg"};

	// vim regex to convert addParam(...) or addInput/Output() to Element:
	//
	// s/add\w\+(create\w\+<\(.*\)>(Vec(\(\d\+\), \(\d\+\)), .*::\(.*\)_\(\w\+\).*/\t\t\1{\2, \3, "\4", "", \4_\5},/
	//
	// Then manually add the human names, min/max/default values from Module::configParam()

	static constexpr std::array<Element, 10> Elements{{
		Davies1900hWhiteKnob{to_mm(20), to_mm(33), "Ch 1 gain", "", ATEN1_PARAM, -1.0, 1.0, 0.0},
		Davies1900hRedKnob{to_mm(20), to_mm(91), "Ch 1 offset", "", OFFSET1_PARAM, -10.0, 10.0, 0.0},
		Davies1900hWhiteKnob{to_mm(20), to_mm(201), "Ch 2 gain", "", ATEN2_PARAM, -1.0, 1.0, 0.0},
		Davies1900hRedKnob{to_mm(20), to_mm(260), "Ch 2 offset", "", OFFSET2_PARAM, -10.0, 10.0, 0.0},
		BefacoInputPort{to_mm(7), to_mm(152), "IN1", "", IN1_INPUT},
		BefacoInputPort{to_mm(7), to_mm(319), "IN2", "", IN2_INPUT},
		BefacoOutputPort{to_mm(43), to_mm(152), "OUT1", "", OUT1_OUTPUT},
		BefacoOutputPort{to_mm(43), to_mm(319), "OUT2", "", OUT2_OUTPUT},
		MediumLight<RedGreenBlueLight>{to_mm(33), to_mm(143), "OUT1", "", OUT1_LIGHT},
		MediumLight<RedGreenBlueLight>{to_mm(33), to_mm(311), "OUT2", "", OUT2_LIGHT},
	}};

	// static constexpr std::span<const Element> Knobs{&Elements[0], 4};
	static constexpr std::span<const Element> InJacks{&Elements[4], 2};
	static constexpr std::span<const Element> OutJacks{&Elements[6], 2};
	static constexpr std::span<const Element> Switches{};
	static constexpr std::span<const Element> Lights{&Elements[8], 2};
};
} // namespace MetaModule
