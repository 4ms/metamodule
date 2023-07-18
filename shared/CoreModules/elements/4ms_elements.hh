#pragma once
#include "base_element.hh"

namespace MetaModule
{

//Knobs
struct Knob9mm : Knob {};
struct DaviesLargeKnob : Knob {};
struct Davies1900hBlackKnob : Knob {};

//Sliders
struct SliderMonoLight : Slider {
	static constexpr size_t NumLights = 1;
};
struct Slider25mmVert : Slider {};
struct Slider25mmHoriz : Slider {};
struct Slider25mmHorizLED : SliderMonoLight {};
struct Slider25mmVertLED : SliderMonoLight {};

//Buttons
struct MomentaryButtonRGB : MomentaryButton {
	static constexpr size_t NumLights = 3;
};
struct MomentaryButtonWhiteLight : MomentaryButton {
	static constexpr size_t NumLights = 1;
};

struct LatchingButtonMonoLight : LatchingButton {
	static constexpr size_t NumLights = 1;
};

//Switches
//TODO: specialize Toggle2pos/3pos

// Encoders
struct EncoderMonoLight : Encoder {
	static constexpr size_t NumLights = 1;
};

struct EncoderRGB : Encoder {
	static constexpr size_t NumLights = 3;
};

struct EncoderWhiteLight : EncoderMonoLight {};
struct SmallEncoder : Encoder {};
struct SmallLEDEncoder : EncoderMonoLight {};

// Input Jacks
struct JackInput4ms : JackInput {};
struct GateJackInput4ms : JackInput4ms {};
struct AnalogJackInput4ms : JackInput4ms {};

// Output jacks
struct JackOutput4ms : JackOutput {};
struct GateJackOutput4ms : JackOutput4ms {};
struct AnalogJackOutput4ms : JackOutput4ms {};

} // namespace MetaModule
