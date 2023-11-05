#pragma once
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

struct Knob : Pot {};
struct Slider : Pot {};

// Switches/Buttons
struct Switch : ParamElement {};

struct MomentaryButton : Switch {
	enum class State_t { PRESSED, RELEASED };
};

struct LatchingButton : Switch {
	enum class State_t { DOWN, UP };
};

struct ToggleSwitch : Switch {};

struct Toggle2pos : ToggleSwitch {
	enum class State_t { DOWN, UP };
};
struct Toggle3pos : ToggleSwitch {
	enum class State_t { DOWN, CENTER, UP };
};
struct Toggle2posHoriz : Toggle2pos {
	enum class State_t { LEFT, RIGHT };
};
struct Toggle3posHoriz : Toggle3pos {
	enum class State_t { LEFT, CENTER, RIGHT };
};

struct SlideSwitchNPos : ToggleSwitch {
	using State_t = unsigned;
	State_t num_pos = 2;
	void *image_bg = nullptr; //TODO: replace void* with std::string_view of filename.png
	void *image_fg = nullptr;
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
