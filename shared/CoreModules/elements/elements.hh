#pragma once
#include "4ms_elements.hh"
#include "AudibleInstruments_elements.hh"
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

using Element = std::variant<NullElement,

							 Knob,
							 Slider,
							 SliderLight,

							 FlipSwitch,
							 SlideSwitch,

							 MomentaryButton,
							 MomentaryButtonWhiteLight,
							 MomentaryButtonRGB,

							 LatchingButton,
							 LatchingButtonMonoLight,

							 //Encoders: TODO: specify knob image
							 Encoder,
							 EncoderRGB,

							 // Jacks: TODO: specify nut image, and signal type?
							 JackInput,
							 JackOutput,
							 // GateJackInput4ms,
							 // AnalogJackInput4ms,
							 // BefacoInputPort,
							 // GateJackOutput4ms,
							 // AnalogJackOutput4ms,
							 // BefacoOutputPort,
							 // PJ301MPortIn,
							 // PJ301MPortOut,

							 //	Lights:TODO! specify image, color(s), and radius ratio for coloration
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

							 // Displays; TODO? Specify a callback for drawing?
							 BraidsDisplay148x56,

							 // Alt Params
							 AltParamToggle2,
							 AltParamToggle3>;

namespace
{
inline constexpr auto ElementSize = sizeof(Element);
}

// helper:
inline BaseElement base_element(const Element &el) {
	return std::visit([](auto e) { return BaseElement{e}; }, el);
}
} // namespace MetaModule
