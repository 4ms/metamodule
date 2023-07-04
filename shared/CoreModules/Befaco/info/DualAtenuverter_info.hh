#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

// Comments are provided to explain how this file was contstructed,
// in hopes that it will help us create a script to convert VCV module code
// to *_info.hh files

// Enums copied from VCV Module:
// They're not strictly necessary but they make the regex easier and improve readability
enum ParamIds { ATEN1_PARAM, OFFSET1_PARAM, ATEN2_PARAM, OFFSET2_PARAM, NUM_PARAMS };
enum InputIds { IN1_INPUT, IN2_INPUT, NUM_INPUTS };
enum OutputIds { OUT1_OUTPUT, OUT2_OUTPUT, NUM_OUTPUTS };
enum LightIds { ENUMS(OUT1_LIGHT, 3), ENUMS(OUT2_LIGHT, 3), NUM_LIGHTS };

namespace MetaModule
{

struct DualAtenuverterInfo : ModuleInfoBase {

	// Slug must match VCV's slug
	static constexpr std::string_view slug{"DualAtenuverter"};

	// Description shows up in MetaModule, can be anything
	static constexpr std::string_view description{"Befaco Dual Attenuvertor"};

	// Width is used by MetaModule to draw the module
	static constexpr uint32_t width_hp = 4;

	// This is only used with the ElementInfo-to-VCV wrapper (vcv/generic_module_new.hh)
	// So it's not used at all if this module only exists in the native plug-in (i.e. VCV Befaco Plugin)
	static constexpr std::string_view svg_filename{"res/modules/Befaco/DualAtenuverter.svg"};

	// Array of all module elements:
	//
	// This is the vim regex to convert addParam(...) or addInput/Output() to Element:
	// s/add\w\+(create\w\+<\(.*\)>(Vec(\(\d\+\), \(\d\+\)), .*::\(.*\)_\(\w\+\).*/\t\t\1{to_mm(\2), to_mm(\3), "\4", "", \4_\5},/
	//
	// Then I manually editted the text names and added the min/max/default values from Module::configParam()
	// And added the excess braces for ParamElements to silence a clang warning [-Wmissing-braces]
	// A smart script could do all this (except perhaps choosing good text names?)

	static constexpr std::array<Element, 10> Elements{
		Davies1900hWhiteKnob{{{{to_mm(20), to_mm(33), "Aten1", "Ch 1 gain", ATEN1_PARAM}, -1.0, 1.0}}},
		Davies1900hRedKnob{{{{to_mm(20), to_mm(91), "Offset1", "Ch 1 offset", OFFSET1_PARAM}, -10.0, 10.0}}},
		Davies1900hWhiteKnob{{{{to_mm(20), to_mm(201), "Aten2", "Ch 2 gain", ATEN2_PARAM}, -1.0, 1.0}}},
		Davies1900hRedKnob{{{{to_mm(20), to_mm(260), "Offset2", "Ch 2 offset", OFFSET2_PARAM}, -10.0, 10.0}}},
		BefacoInputPort{to_mm(7), to_mm(152), "IN1", "Ch 1 In", IN1_INPUT},
		BefacoInputPort{to_mm(7), to_mm(319), "IN2", "Ch 2 In", IN2_INPUT},
		BefacoOutputPort{to_mm(43), to_mm(152), "OUT1", "Ch 1 Out", OUT1_OUTPUT},
		BefacoOutputPort{to_mm(43), to_mm(319), "OUT2", "Ch 2 Out", OUT2_OUTPUT},
		MediumLight<RedGreenBlueLight>{to_mm(33), to_mm(143), "OUT1", "", OUT1_LIGHT},
		MediumLight<RedGreenBlueLight>{to_mm(33), to_mm(311), "OUT2", "", OUT2_LIGHT},
	};
};

} // namespace MetaModule
