#pragma once
#include <string_view>
#include <variant>

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
// Generic

struct BipolarColor_t {
	float value;
};

enum class Coords { Center, TopLeft };

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

//
// ParamElement: base class for pot, encoder, switch/button
//

struct ParamElement : BaseElement {
	static constexpr size_t NumParams = 1;
};

//
// Pots (Knobs, Sliders)
//
struct Pot : ParamElement {
	using State_t = float;
};

struct Knob : Pot {};
struct Slider : Pot {};

// Knobs
struct BefacoTinyKnob : Knob {};
struct BefacoBigKnob : Knob {};
struct DaviesLargeKnob : Knob {};
struct Davies1900hBlackKnob : Knob {};
struct Davies1900hWhiteKnob : Knob {};
struct Davies1900hRedKnob : Knob {};
struct Davies1900hLargeGreyKnob : Knob {};
struct Davies1900hLightGreyKnob : Knob {};
struct Davies1900hDarkGreyKnob : Knob {};
struct Davies1900hLargeLightGreyKnob : Knob {};
struct Davies1900hLargeWhiteKnob : Knob {};
struct Knob9mm : Knob {};
struct BefacoTinyKnobWhite : Knob {};
struct BefacoTinyKnobRed : Knob {};
struct BefacoTinyKnobDarkGrey : Knob {};
struct BefacoTinyKnobLightGrey : Knob {};
struct BefacoTinyKnobBlack : Knob {};
struct Rogan2SGray : Knob {};
struct Rogan2PSWhite : Knob {};
struct Rogan2PSGreen : Knob {};
struct Rogan2PSRed : Knob {};

// Sliders
struct SliderMonoLight : Slider {
	static constexpr size_t NumLights = 1;
};

struct BefacoSlidePot : Slider { // TODO: is using this enum better than two types (Hor/Ver)?
								 // enum Orientation { Vertical, Horizontal };
								 // static constexpr Orientation orientation = Orientation::Vertical;
};
struct BefacoSlidePotSmall : Slider {};
struct Slider25mmVert : Slider {};
struct Slider25mmHoriz : Slider {};
struct Slider25mmHorizLED : SliderMonoLight {};
struct Slider25mmVertLED : SliderMonoLight {};

//
// Switches/Buttons
//
struct Switch : ParamElement {};

struct MomentaryButton : Switch {
	enum class State_t { PRESSED, RELEASED };
};
struct MomentaryButtonRGB : MomentaryButton {
	static constexpr size_t NumLights = 3;
};
struct MomentaryButtonWhiteLight : MomentaryButton {
	static constexpr size_t NumLights = 1;
};

struct LatchingButton : Switch {
	enum class State_t { DOWN, UP };
};
struct LatchingButtonMonoLight : LatchingButton {
	static constexpr size_t NumLights = 1;
};

struct Toggle2pos : Switch {
	enum class State_t { DOWN, UP };
};
struct Toggle3pos : Switch {
	enum class State_t { DOWN, CENTER, UP };
};
struct Toggle2posHoriz : Toggle2pos {};
struct Toggle3posHoriz : Toggle3pos {};

struct BefacoPush : MomentaryButton {};
struct BefacoSwitch : Toggle2pos {};
struct BefacoSwitchHorizontal : Toggle2pos {};

//
// Encoders
//
struct Encoder : ParamElement {};
struct EncoderMonoLight : Encoder {
	static constexpr size_t NumLights = 1;
};

struct EncoderRGB : Encoder {
	static constexpr size_t NumLights = 3;
};

struct EncoderWhiteLight : EncoderMonoLight {};
struct SmallEncoder : Encoder {};
struct SmallLEDEncoder : EncoderMonoLight {};

//
// Jacks
//
struct JackElement : BaseElement {};

struct JackInput : JackElement {
	static constexpr size_t NumInputs = 1;
};
struct JackOutput : JackElement {
	static constexpr size_t NumOutputs = 1;
};

// Input Jacks
struct GateJackInput : JackInput {};
struct AnalogJackInput : JackInput {};
struct BefacoInputPort : JackInput {};
using BananutBlack = BefacoInputPort;
struct JackInput4ms : JackInput {};
struct GateJackInput4ms : JackInput4ms {};
struct AnalogJackInput4ms : JackInput4ms {};

// Output jacks
struct BefacoOutputPort : JackOutput {};
using BananutRed = BefacoOutputPort;
struct JackOutput4ms : JackOutput {};
struct GateJackOutput4ms : JackOutput4ms {};
struct AnalogJackOutput4ms : JackOutput4ms {};
struct PJ301MPortIn : JackInput {};
struct PJ301MPortOut : JackOutput {};

//
// Lights (non-composite)
//

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
template<typename LedT>
struct MediumLight : LedT {};

//
// Displays
//
struct Display : LightElement {}; //TODO: does this need its own category?
struct BraidsDisplay148x56 : Display {};

//
// AltParams: TODO
//
struct AltParam : BaseElement {};
struct AltParamToggle2 : AltParam {};
struct AltParamToggle3 : AltParam {};

//
// All Concrete Elements
//
using Element = std::variant<
	// Knobs
	Davies1900hBlackKnob,
	Knob9mm,
	DaviesLargeKnob,
	Davies1900hRedKnob,
	Davies1900hWhiteKnob,
	BefacoBigKnob,
	BefacoTinyKnob,
	BefacoTinyKnobWhite,
	BefacoTinyKnobRed,
	BefacoTinyKnobDarkGrey,
	BefacoTinyKnobLightGrey,
	BefacoTinyKnobBlack,
	Davies1900hLargeWhiteKnob,
	Davies1900hLargeLightGreyKnob,
	Davies1900hLargeGreyKnob,
	Davies1900hLightGreyKnob,
	Davies1900hDarkGreyKnob,
	Rogan2SGray,
	Rogan2PSWhite,
	Rogan2PSGreen,
	Rogan2PSRed,

	// Sliders
	Slider25mmVert,
	Slider25mmHoriz,
	Slider25mmVertLED,
	Slider25mmHorizLED,
	BefacoSlidePotSmall,
	BefacoSlidePot,

	// Switches/Buttons
	MomentaryButtonRGB,
	MomentaryButtonWhiteLight,
	LatchingButtonMonoLight,
	BefacoPush,
	Toggle2pos,
	Toggle3pos,
	Toggle2posHoriz,
	Toggle3posHoriz,
	BefacoSwitch,
	BefacoSwitchHorizontal,

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
	MediumLight<RedGreenBlueLight>,
	MediumLight<GreenRedLight>,
	MediumLight<RedLight>,
	MediumLight<YellowLight>,
	MediumLight<GreenLight>,
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

} // namespace MetaModule
