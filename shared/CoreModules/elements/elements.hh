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

// Criteria for being a member of the variant. Either:
// - Unique NumParams/NumLights/NumInputs/NumOutputs values (because these are static constexpr).
// - Unique data members (avoid unused data members in types)
//
// Also, if any of the following are true, it is not strictly required to have entry in Elements,
// but it should be considered to avoid too many "type" fields.
// - Unique animation or drawing method (e.g.: Having two types Slider and Knob is preferred to having Pot::is_slider).
// - Unique set of values or method of interpreting values (e.g. Momentary vs Latched buttons)

using Element = std::variant<
	// Placeholder for unknown element
	NullElement,

	// Knobs
	// TODO: all these become just `Knob`
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
	// TODO: all these become just `Slider`
	Slider25mmVert,
	Slider25mmHoriz,
	Slider25mmVertLED,
	Slider25mmHorizLED,
	BefacoSlidePotSmall,
	BefacoSlidePot,
	Crossfader,

	// Switches/Buttons
	FlipSwitch,
	SlideSwitch,

	// TODO: how to break these up? Mom/Latched * 0/1/2/3LEDs = 8 types?
	// Or is Mom/Latched a data members?
	MomentaryButton,		   //no light
	MomentaryButtonWhiteLight, //one light
	MomentaryButtonRGB,		   //three lights

	LatchingButton,
	// TODO REMOVE;
	LatchingButtonMonoLight,

	// MomentaryButton:
	// BefacoPush,
	// TL1105,
	// CKD6,

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
	VCVLightBezel<RedGreenBlueLight>,
	LEDBezel,
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
