#pragma once
#include "util/colors_rgb565.hh"
#include <array>
#include <cstdint>
#include <string_view>

// Hierarchy:
//                                                   BaseElement
//                     +---------------------------------'--------------+---------------------------+-------------------------------+
//                     |                                                |                           |                               |
//              ParamElement                                        JackElement                  LightElement                   AltParam
//     +----------+---'--------+------------------+                +------'-----+         +---------+'-------+---------+
//     |          |            |                  |                |            |         |         |        |         |
//    Pot     Encoder       Switch              Button          JackInput  JackOutput  MonoLight DualLight RGBLight Display
//  +--'--+        |     +----'---+          +----'---------+
//  |     |        |     |        |          |              |
// Knob  Slider    |   FlipSw  SlideSw    MomBut         LatchingBut
//        |        |                     +---'---+          |
//        |        |                     |       |          |
//   SliderLight  EncoderRGB      MomButWhite MomButRGB   LatButMonoLight
//

namespace MetaModule
{

enum class Coords { Center, TopLeft };

struct BipolarColor_t {
	float value;
};

struct FullColor_t {
	float value;
};

struct BaseElement {
	float x_mm = 0;
	float y_mm = 0;
	Coords coords = Coords::Center;

	std::string_view short_name;
	std::string_view long_name;

	static constexpr size_t NumParams = 0;
	static constexpr size_t NumLights = 0;
	static constexpr size_t NumInputs = 0;
	static constexpr size_t NumOutputs = 0;

	// This needs to be there to catch no State_t defined by children
	using State_t = void;
};

struct ImageElement : BaseElement {
	std::string_view image = "";
};

struct NullElement : BaseElement {};

// ParamElement: base class for pot, encoder, switch/button
struct ParamElement : ImageElement {
	static constexpr size_t NumParams = 1;
};

// Pots (Knobs, Sliders)
struct Pot : ParamElement {
	using State_t = float;
};

struct Knob : Pot {};

struct Slider : Pot {
	std::string_view image_handle = "";
};

struct SliderLight : Slider {
	static constexpr size_t NumLights = 1;
	RGB565 color = Colors565::White;
};

//
// Buttons
//
struct Button : ParamElement {};

struct MomentaryButton : Button {
	enum class State_t { PRESSED, RELEASED };
};

struct MomentaryButtonRGB : MomentaryButton {
	static constexpr size_t NumLights = 3;
};
struct MomentaryButtonWhiteLight : MomentaryButton {
	static constexpr size_t NumLights = 1;
};

// LatchingButton always has a single color LED
// It's drawn with a single frame, and the color is applied as a filled circle,
// whose alpha value equals the LED value
struct LatchingButton : Button {
	enum class State_t { DOWN, UP };
	static constexpr size_t NumLights = 1;
	RGB565 color = Colors565::White;
};

//
// Switches
//
struct Switch : ParamElement {};

// FlipSwitch has up to 3 frames
// Frame n is drawn to indicate value == n/(num_pos-1)
struct FlipSwitch : Switch {
	using State_t = unsigned;
	unsigned num_pos = 3;
	std::array<std::string_view, 3> frames{};
	std::array<std::string_view, 3> pos_names{"0", "1", "2"};
};

// SlideSwitch has a bg (body) image and a fg (handle) image
// The handle is drawn at evenly spaced positions to indicate the switch's value
struct SlideSwitch : Switch {
	using State_t = unsigned;
	State_t num_pos = 2;
	std::string_view image_handle = "";
	enum class Ascend { UpLeft, DownRight } direction = Ascend::DownRight;
	std::array<std::string_view, 8> pos_names{};
};

// Encoders
struct Encoder : ParamElement {};

struct EncoderRGB : Encoder {
	static constexpr size_t NumLights = 3;
};

// Jacks
struct JackElement : ImageElement {};

struct JackInput : JackElement {
	static constexpr size_t NumInputs = 1;
};

struct JackOutput : JackElement {
	static constexpr size_t NumOutputs = 1;
};

// Lights
struct LightElement : ImageElement {};

struct MonoLight : LightElement {
	static constexpr size_t NumLights = 1;
	RGB565 color = Colors565::White;
};

struct DualLight : LightElement {
	static constexpr size_t NumLights = 2;
	std::array<RGB565, 2> color = {Colors565::White, Colors565::White};
};
struct RgbLight : LightElement {
	static constexpr size_t NumLights = 3;
};

// Displays
struct Display : LightElement {}; //TODO: does this need its own category?

// AltParams:
// Like Params but they are not drawn on the faceplate (access by menu only)
struct AltParamElement : BaseElement {
	static constexpr size_t NumParams = 1;
};

struct AltParamContinuous : AltParamElement {
	using State_t = float;
	State_t DefaultValue = 0.5f;
	State_t MinValue = 0.0f;
	State_t MaxValue = 1.0f;
};

struct AltParamChoice : AltParamElement {
	using State_t = unsigned;

	unsigned num_pos = 2;
	State_t DefaultValue = 0;
};

struct AltParamChoiceLabeled : AltParamChoice {
	static constexpr size_t MaxChoices = 8;
	std::array<std::string_view, MaxChoices> pos_names{};
};

} // namespace MetaModule
