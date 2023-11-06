#pragma once
#include <array>
#include <string_view>

// Heirarchy:
//                                                         BaseElement
//                     |---------------------------------------'------------|---------------------------|
//              ParamElement                                          JackElement                  LightElement
//     |--------------'----------------|------------------|         |------'-----|          |---------|-'------|---------|
//    Pot                           Switch             Encoder    JackInput    JackOutput   MonoLight DualLight RGBLight Display
//  |--'---|                 |--------'|----------|        |
// Knob Slider             MomBut LatchingBut Toggle       |
//  |       |                 |       |                    |
// ...    ...,SliderLED     *MonoLight/RGB          EncoderRGB
//

namespace MetaModule
{

enum class Coords { Center, TopLeft };

struct BipolarColor_t {
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

struct NullElement : BaseElement {};

// ParamElement: base class for pot, encoder, switch/button
struct ParamElement : BaseElement {
	static constexpr size_t NumParams = 1;
};

// Pots (Knobs, Sliders)
struct Pot : ParamElement {
	using State_t = float;
};

//TODO: rename KnobE => Knob and remove current "Knob"
struct KnobE : Pot {
	std::string_view image = "";
};

struct Knob : Pot {};
struct Slider : Pot {};

//
// Buttons
//
struct Button : ParamElement {
	std::string_view image = "";
};

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
	uint16_t color = 0xfd40;
	//float color_radius_ratio?
};

//TODO: change svg script to use LatchingButton, not the alias
// using LatchingButtonMonoLight = LatchingButton;
struct LatchingButtonMonoLight : ParamElement {
	enum class State_t { DOWN, UP };
	static constexpr size_t NumLights = 1;
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
	std::string_view image_bg = "";
	std::string_view image_fg = "";
};

// Encoders
struct Encoder : ParamElement {};

// Jacks
struct JackElement : BaseElement {};

struct JackInput : JackElement {
	static constexpr size_t NumInputs = 1;
};
struct JackOutput : JackElement {
	static constexpr size_t NumOutputs = 1;
};

// Lights
struct LightElement : BaseElement {
	static constexpr size_t NumLights = 1;
};
struct MonoLight : LightElement {};
struct DualLight : LightElement {
	static constexpr size_t NumLights = 2;
};
struct RgbLed : LightElement {
	static constexpr size_t NumLights = 3;
};

struct RedLight : MonoLight {};
struct OrangeLight : MonoLight {};
struct YellowLight : MonoLight {};
struct GreenLight : MonoLight {};
struct BlueLight : MonoLight {};
struct WhiteLight : MonoLight {};
struct RedBlueLight : DualLight {};
struct GreenRedLight : DualLight {};
struct RedGreenBlueLight : RgbLed {};

// Displays
struct Display : LightElement {}; //TODO: does this need its own category?

// AltParams: TODO
struct AltParam : BaseElement {};
struct AltParamToggle2 : AltParam {};
struct AltParamToggle3 : AltParam {};

} // namespace MetaModule
