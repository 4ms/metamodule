#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>
#include <string_view>

// Comments are provided to explain how this file was contstructed,
// in hopes that it will help us create a script to convert VCV module code
// to *_info.hh files

namespace MetaModule
{

struct DualAtenuverterInfo : ModuleInfoBase {
	// Slug must match VCV's slug
	static constexpr std::string_view slug{"DualAtenuverter"};

	// Description shows up in MetaModule, can be anything
	static constexpr std::string_view description{"Befaco Dual Attenuvertor"};

	// Width is used by MetaModule to draw the module
	static constexpr uint32_t width_hp = 4;

	// uses_center_coords refers to whether the x,y coordinates in the Elements array
	// are the center or top-left position of the element.
	// If the VCV ModuleWidget contstructor uses create*Centered(...), then set this to true
	// There is no way to use some center coordinates and some top/left coordinates in the same module
	// (but it can be made to work if we need it)
	static constexpr bool uses_center_coords = false;

	// Array of all module elements:
	//
	// This is the vim regex to convert addParam(...) or addInput/Output() to Element:
	// s/add\w\+(create\w\+<\(.*\)>(Vec(\(\d\+\), \(\d\+\)), .*::\(.*\)_\(\w\+\).*/\t\t\1{to_mm(\2), to_mm(\3), "\4", "", \4_\5},/
	//
	// Then I manually editted the text names

	static constexpr std::array<Element, 10> Elements{
		Davies1900hWhiteKnob{to_mm(20), to_mm(33), "Aten1", "Ch 1 gain"},
		Davies1900hRedKnob{to_mm(20), to_mm(91), "Offset1", "Ch 1 offset"},
		Davies1900hWhiteKnob{to_mm(20), to_mm(201), "Aten2", "Ch 2 gain"},
		Davies1900hRedKnob{to_mm(20), to_mm(260), "Offset2", "Ch 2 offset"},
		BefacoInputPort{to_mm(7), to_mm(152), "IN1", "Ch 1 In"},
		BefacoInputPort{to_mm(7), to_mm(319), "IN2", "Ch 2 In"},
		BefacoOutputPort{to_mm(43), to_mm(152), "OUT1", "Ch 1 Out"},
		BefacoOutputPort{to_mm(43), to_mm(319), "OUT2", "Ch 2 Out"},
		MediumLight<RedGreenBlueLight>{to_mm(33), to_mm(143), "OUT1", ""},
		MediumLight<RedGreenBlueLight>{to_mm(33), to_mm(311), "OUT2", ""},
	};
};

} // namespace MetaModule
