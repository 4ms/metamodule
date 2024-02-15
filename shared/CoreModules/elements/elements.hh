#pragma once
#include "base_element.hh"
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

							 Encoder,
							 EncoderRGB,

							 JackInput,
							 JackOutput,

							 MonoLight,
							 DualLight,
							 RgbLight,

							 Display, //TODO

							 AltParamContinuous,
							 AltParamChoice>;

namespace
{
inline constexpr auto ElementSize = sizeof(Element);
}

// helper:
inline BaseElement base_element(const Element &el) {
	return std::visit([](auto e) { return BaseElement{e}; }, el);
}
} // namespace MetaModule
