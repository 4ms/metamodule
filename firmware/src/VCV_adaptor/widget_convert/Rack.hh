#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/componentlibrary.hpp"
#include "VCV_adaptor/widget_convert/base.hh"

namespace MetaModule
{

//
// Buttons/switches
//
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
	return MomentaryButton{b, "BefacoPush_0.png"};
};

template<>
inline Element make_element<rack::componentlibrary::CKD6>(BaseElement b) {
	return MomentaryButton{b, "CKD6_0.png"};
};

template<>
inline Element make_element<rack::componentlibrary::TL1105>(BaseElement b) {
	return MomentaryButton{b, "TL1105.png"};
};

template<>
inline Element make_element<rack::componentlibrary::LEDBezel>(BaseElement b) {
	return MomentaryButton{b, "VCVBezel.png"};
};

template<>
inline Element
make_element<rack::componentlibrary::VCVLightBezel<rack::componentlibrary::RedGreenBlueLight>>(BaseElement b) {
	return MomentaryButtonRGB{b, "VCVBezel.png"};
};

//
// Knobs
//

template<>
inline Element make_element<rack::componentlibrary::BefacoBigKnob>(BaseElement b) {
	return Knob{b, "BefacoBigKnob.png"};
};

template<>
inline Element make_element<rack::componentlibrary::BefacoTinyKnob>(BaseElement b) {
	return Knob{b, "BefacoTinyKnobWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hBlackKnob>(BaseElement b) {
	return Knob{b, "Davies1900hBlack.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hWhiteKnob>(BaseElement b) {
	return Knob{b, "Davies1900hWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hRedKnob>(BaseElement b) {
	return Knob{b, "Davies1900hRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Davies1900hLargeWhiteKnob>(BaseElement b) {
	return Knob{b, "Davies1900hLargeWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSGreen>(BaseElement b) {
	return Knob{b, "Rogan1PSGreen.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSRed>(BaseElement b) {
	return Knob{b, "Rogan1PSRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PSWhite>(BaseElement b) {
	return Knob{b, "Rogan1PSWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2SGray>(BaseElement b) {
	return Knob{b, "Rogan2SGray.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSWhite>(BaseElement b) {
	return Knob{b, "Rogan2PSWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan1PRed>(BaseElement b) {
	return Knob{b, "Rogan1PRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan>(BaseElement b) {
	return Knob{b, "Rogan1PRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSRed>(BaseElement b) {
	return Knob{b, "Rogan2PSRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan2PSGreen>(BaseElement b) {
	return Knob{b, "Rogan2PSGreen.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSWhite>(BaseElement b) {
	return Knob{b, "Rogan3PSWhite.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSRed>(BaseElement b) {
	return Knob{b, "Rogan3PSRed.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Rogan3PSGreen>(BaseElement b) {
	return Knob{b, "Rogan3PSGreen.png"};
};

template<>
inline Element make_element<rack::componentlibrary::Trimpot>(BaseElement b) {
	return Knob{b, "Trimpot.png"};
};

//
// Sliders
//

template<>
inline Element make_element<rack::componentlibrary::BefacoSlidePot>(BaseElement b) {
	return Slider{{b, "BefacoSlidePot_bg.png"}, "BefacoSlidePot_fg.png"};
};

//
// Lights
//

// SmallLight

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::RedLight>>(BaseElement b) {
	return MonoLight{{b, "SmallLight.png"}, Colors565::Red};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::GreenLight>>(BaseElement b) {
	return MonoLight{{b, "SmallLight.png"}, Colors565::Green};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::BlueLight>>(BaseElement b) {
	return MonoLight{{b, "SmallLight.png"}, Colors565::Cyan};
};

template<>
inline Element make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::GreenRedLight>>(BaseElement b) {
	return DualLight{{b, "SmallLight.png"}, {Colors565::Green, Colors565::Red}};
};

template<>
inline Element
make_element<rack::componentlibrary::SmallLight<rack::componentlibrary::RedGreenBlueLight>>(BaseElement b) {
	return RgbLight{{b, "SmallLight.png"}};
};

// MediumLight

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::RedLight>>(BaseElement b) {
	return MonoLight{{b, "MediumLight.png"}, Colors565::Red};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::GreenLight>>(BaseElement b) {
	return MonoLight{{b, "MediumLight.png"}, Colors565::Green};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::BlueLight>>(BaseElement b) {
	return MonoLight{{b, "MediumLight.png"}, Colors565::Cyan};
};

template<>
inline Element make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::GreenRedLight>>(BaseElement b) {
	return DualLight{{b, "MediumLight.png"}, {Colors565::Green, Colors565::Red}};
};

template<>
inline Element
make_element<rack::componentlibrary::MediumLight<rack::componentlibrary::RedGreenBlueLight>>(BaseElement b) {
	return RgbLight{{b, "MediumLight.png"}};
};

// LargeLight

template<>
inline Element make_element<rack::componentlibrary::LargeLight<rack::componentlibrary::RedLight>>(BaseElement b) {
	return MonoLight{{b, "LargeLight.png"}, Colors565::Red};
};

template<>
inline Element make_element<rack::componentlibrary::LargeLight<rack::componentlibrary::GreenLight>>(BaseElement b) {
	return MonoLight{{b, "LargeLight.png"}, Colors565::Green};
};

template<>
inline Element make_element<rack::componentlibrary::LargeLight<rack::componentlibrary::BlueLight>>(BaseElement b) {
	return MonoLight{{b, "LargeLight.png"}, Colors565::Cyan};
};

template<>
inline Element make_element<rack::componentlibrary::LargeLight<rack::componentlibrary::GreenRedLight>>(BaseElement b) {
	return DualLight{{b, "LargeLight.png"}, {Colors565::Green, Colors565::Red}};
};

template<>
inline Element
make_element<rack::componentlibrary::LargeLight<rack::componentlibrary::RedGreenBlueLight>>(BaseElement b) {
	return RgbLight{{b, "LargeLight.png"}};
};

//
// Jacks
//

// Inputs

// template<>
// inline Element make_element_input<rack::componentlibrary::PJ301MPort>(BaseElement b) {
// 	return JackInput{b, "jack_x.png"};
// };

// template<>
// inline Element make_element_input<rack::componentlibrary::ThemedPJ301MPort>(BaseElement b) {
// 	return JackInput{b, "jack_x.png"};
// };

// Outputs

// template<>
// inline Element make_element_output<rack::componentlibrary::PJ301MPort>(BaseElement b) {
// 	return JackOutput{b, "jack_x.png"};
// };

// template<>
// inline Element make_element_output<rack::componentlibrary::ThemedPJ301MPort>(BaseElement b) {
// 	return JackOutput{b, "jack_x.png"};
// };

} // namespace MetaModule
