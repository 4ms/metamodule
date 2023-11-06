#pragma once
#include "4ms_elements.hh"
#include "AudibleInstruments_elements.hh"
#include "Befaco_elements.hh"
#include "Rack_elements.hh"
#include "base_element.hh"
#include <string_view>
#include <variant>

namespace MetaModule
{
using Element = std::variant<
	// Placeholder for unknown element
	NullElement,

	// Knobs
	Knob9mm,
	Davies1900hRedKnob,
	Davies1900hBlackKnob,
	Davies1900hWhiteKnob,
	Davies1900hDarkGreyKnob,
	Davies1900hLightGreyKnob,
	DaviesLargeKnob,
	Davies1900hLargeGreyKnob,
	Davies1900hLargeWhiteKnob,
	Davies1900hLargeLightGreyKnob,
	BefacoBigKnob,
	BefacoTinyKnobRed,
	BefacoTinyKnobBlack,
	BefacoTinyKnobWhite,
	BefacoTinyKnobDarkGrey,
	BefacoTinyKnobLightGrey,
	Rogan1PRed,
	Rogan1PSGreen,
	Rogan1PSRed,
	Rogan1PSWhite,
	Rogan2SGray,
	Rogan2PSWhite,
	Rogan2PSGreen,
	Rogan2PSRed,
	Rogan3PSWhite,
	Rogan3PSRed,
	Rogan3PSGreen,
	Trimpot,

	// Sliders
	Slider25mmVert,
	Slider25mmHoriz,
	Slider25mmVertLED,
	Slider25mmHorizLED,
	BefacoSlidePotSmall,
	BefacoSlidePot,
	Crossfader,

	// Switches/Buttons
	MomentaryButtonRGB,
	MomentaryButtonWhiteLight,
	LatchingButtonMonoLight,
	BefacoPush,
	//TODO: All four toggles replaced by Toggle, with members for num_pos and horiz/vert
	Toggle2pos,
	Toggle3pos,
	Toggle2posHoriz,
	Toggle3posHoriz,

	SlideSwitchNPos,

	BefacoSwitch,
	BefacoSwitchHorizontal,
	VCVLightBezel<RedGreenBlueLight>,
	LEDBezel,
	CKSS,
	CKSSRot,
	TL1105,
	CKD6,

	//Encoders
	Encoder,
	EncoderWhiteLight,
	EncoderRGB,

	// Jacks
	GateJackInput4ms,
	AnalogJackInput4ms,
	BefacoInputPort,
	GateJackOutput4ms,
	AnalogJackOutput4ms,
	BefacoOutputPort,
	PJ301MPortIn,
	PJ301MPortOut,

	//	Lights
	MediumLight<RedGreenBlueLight>,
	MediumLight<GreenRedLight>,
	MediumLight<RedLight>,
	MediumLight<YellowLight>,
	MediumLight<GreenLight>,
	SmallLight<BlueLight>,
	SmallLight<RedLight>,
	SmallLight<GreenLight>,
	SmallLight<GreenRedLight>,
	RedGreenBlueLight,
	RedLight,
	OrangeLight,
	GreenLight,
	BlueLight,
	WhiteLight,
	RedBlueLight,

	// Displays
	BraidsDisplay148x56,

	// Alt Params
	AltParamToggle2,
	AltParamToggle3>;

// helper:
inline BaseElement base_element(const Element &el) {
	return std::visit([](auto e) { return BaseElement{e}; }, el);
}
} // namespace MetaModule
