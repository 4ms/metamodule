#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"
#include "VCV_adaptor/widgets.hh"

namespace MetaModule
{

template<>
inline Element make_element<rack::componentlibrary::BefacoSwitch>(BaseElement b) {
	return FlipSwitch{
		{b}, 3, {"BefacoSwitch_0.png", "BefacoSwitch_1.png", "BefacoSwitch_2.png"}, {"Down", "Center", "Up"}};
};

template<>
inline Element make_element<rack::componentlibrary::CKSS>(BaseElement b) {
	return FlipSwitch{{b}, 2, {"CKSS_0.png", "CKSS_1.png"}};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoPush>(BaseElement b) {
	return MomentaryButton{{{b}, "BefacoPush_0.png"}};
};

template<>
inline Element make_element<rack::componentlibrary::CKD6>(BaseElement b) {
	return MomentaryButton{{{b}, "CKD6_0.png"}};
};

template<>
inline Element make_element<rack::componentlibrary::TL1105>(BaseElement b) {
	return MomentaryButton{{{b}, "TL1105.png"}};
};

template<>
inline Element make_element<rack::componentlibrary::LEDBezel>(BaseElement b) {
	return LEDBezel{{{{b}}}}; //TODO... is this a MomentaryButton with LED?
};

template<>
inline Element make_element<rack::componentlibrary::BefacoBigKnob>(BaseElement b) {
	return Knob{{b}, "BefacoBigKnob.png"};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoTinyKnob>(BaseElement b) {
	return Knob{{b}, "BefacoTinyKnobWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hBlackKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hBlackKnob.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hWhiteKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hWhiteKnob.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hRedKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hRedKnob.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hLargeWhiteKnob>(BaseElement b) {
	return Knob{{b}, "Davies1900hLargeWhiteKnob.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSGreen>(BaseElement b) {
	return Knob{{b}, "Rogan1PSGreen.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSRed>(BaseElement b) {
	return Knob{{b}, "Rogan1PSRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSWhite>(BaseElement b) {
	return Knob{{b}, "Rogan1PSWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2SGray>(BaseElement b) {
	return Knob{{b}, "Rogan2SGray.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSWhite>(BaseElement b) {
	return Knob{{b}, "Rogan2PSWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PRed>(BaseElement b) {
	return Knob{{b}, "Rogan1PRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan>(BaseElement b) {
	return Knob{{b}, "Rogan1PRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSRed>(BaseElement b) {
	return Knob{{b}, "Rogan2PSRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSGreen>(BaseElement b) {
	return Knob{{b}, "Rogan2PSGreen.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSWhite>(BaseElement b) {
	return Knob{{b}, "Rogan3PSWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSRed>(BaseElement b) {
	return Knob{{b}, "Rogan3PSRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSGreen>(BaseElement b) {
	return Knob{{b}, "Rogan3PSGreen.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Trimpot>(BaseElement b) {
	return Knob{{b}, "Trimpot.png"};
};

//
// Sliders
//
template<>
inline Element make_element<rack::componentlibrary::BefacoSlidePot>(BaseElement b) {
	return Slider{{b}, "BefacoSlidePot.png", "BefacoSlidePotHandle.png"};
};

//
// Lights
//

template<>
inline Element
make_element<rack::componentlibrary::VCVLightBezel<rack::componentlibrary::RedGreenBlueLight>>(BaseElement b) {
	return VCVLightBezel<RedGreenBlueLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::RedLight>>(BaseElement b) {
	return SmallLight<RedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::GreenLight>>(BaseElement b) {
	return SmallLight<GreenLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::GreenRedLight>>(BaseElement b) {
	return SmallLight<GreenRedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::GreenRedLight>>(BaseElement b) {
	return MediumLight<GreenRedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::RedLight>>(BaseElement b) {
	return MediumLight<RedLight>{b};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::GreenLight>>(BaseElement b) {
	return MediumLight<GreenLight>{b};
};

//
// Jacks
//

// Inputs

template<>
inline Element make_element_input<rack::componentlibrary::PJ301MPort>(BaseElement b) {
	return JackInput{{{b}, "jack_x.png"}};
};

template<>
inline Element make_element_input<rack::componentlibrary::ThemedPJ301MPort>(BaseElement b) {
	return JackInput{{{b}, "jack_x.png"}};
};

// Outputs

template<>
inline Element make_element_output<rack::componentlibrary::PJ301MPort>(BaseElement b) {
	return JackOutput{{{b}, "jack_x.png"}};
};

template<>
inline Element make_element_output<rack::componentlibrary::ThemedPJ301MPort>(BaseElement b) {
	return JackOutput{{{b}, "jack_x.png"}};
};

} // namespace MetaModule
