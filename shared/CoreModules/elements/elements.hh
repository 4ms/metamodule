#pragma once
#include "4ms_elements.hh" //TODO: don't put this here, put it in info files
#include "base_element.hh"
#include <string_view>
#include <variant>

namespace MetaModule
{

// Criteria for being a member of the variant.
// - Unique NumParams/NumLights/NumInputs/NumOutputs values (because these are static constexpr).
// - Unique data members (e.g. SlideSwitch::num_pos)
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

							 Encoder,
							 EncoderRGB,

							 JackInput,
							 JackOutput,

							 //	Lights:TODO! specify image, color(s), and radius ratio for coloration
							 //Rack:
							 MonoLight,
							 DualLight,
							 RgbLight,

							 // VCVLightBezel<RedGreenBlueLight>,
							 // MediumLight<RedGreenBlueLight>,
							 // MediumLight<GreenRedLight>,
							 // MediumLight<RedLight>,
							 // MediumLight<YellowLight>,
							 // MediumLight<GreenLight>,
							 // SmallLight<BlueLight>,
							 // SmallLight<RedLight>,
							 // SmallLight<GreenLight>,
							 // SmallLight<GreenRedLight>,

							 // 							 RedGreenBlueLight,
							 // 							 RedLight,
							 // 							 OrangeLight,
							 // 							 GreenLight,
							 // 							 BlueLight,
							 // 							 WhiteLight,
							 // 							 RedBlueLight,

							 // Displays; TODO? Specify a callback for drawing?
							 Display,
							 // BraidsDisplay148x56,

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
