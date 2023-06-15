#pragma once
#include <string_view>
#include <variant>

namespace MetaModule
{

struct BaseElement {
	float x_mm = 0;
	float y_mm = 0;

	std::string_view short_name;
	std::string_view long_name;
	unsigned idx = 0;
	float min_val = 0.f;
	float max_val = 1.f;
	float default_val = 0.f;
};

// Lights

struct Light : BaseElement {};
struct MonoLight : Light {};
struct RedLight : MonoLight {};
struct OrangeLight : MonoLight {};
struct GreenLight : MonoLight {};
struct BlueLight : MonoLight {};
struct WhiteLight : MonoLight {};

struct DualLight : Light {};
struct RedBlueLight : DualLight {
	enum Color { RED, BLUE };
};

struct RgbLed : Light {
	enum Color { RED, BLUE, GREEN };
};
using RedGreenBlueLight = RgbLed;

template<typename LedT>
struct MediumLight : Light {};
template<>
struct MediumLight<RedGreenBlueLight> : RedGreenBlueLight {};

// Switches/Buttons

struct Switch : BaseElement {};
struct MomentaryButton : Switch {
	enum State { PRESSED, RELEASED };
};
struct MomentaryButtonRGB : MomentaryButton {
	enum Color { RED, BLUE, GREEN };
};
struct LatchingButton : Switch {
	enum State { DOWN, UP };
};
struct LatchingButtonMonoLight : LatchingButton {
	enum Color { RED, BLUE, GREEN };
};
struct Toggle2pos : Switch {
	enum State { DOWN, UP };
};
struct Toggle3pos : Switch {
	enum State { DOWN, CENTER, UP };
};
struct BefacoSwitchHorizontal : Switch {};

// Encoders
struct Encoder : Switch {};
struct LEDEncoder : Encoder {};
struct SmallEncoder : Encoder {};
struct SmallLEDEncoder : Encoder {};

// Pots (Knobs, Sliders)
struct Pot : BaseElement {};
struct Knob : Pot {};
struct Slider : Pot {};

struct BefacoTinyKnob : Knob {};
struct DaviesLargeKnob : Knob {};
struct Davies1900hBlackKnob : Knob {};
struct Davies1900hWhiteKnob : Knob {};
struct Davies1900hRedKnob : Knob {};
struct Davies1900hLargeGreyKnob : Knob {};
struct Davies1900hLightGreyKnob : Knob {};
struct Davies1900hDarkGreyKnob : Knob {};
struct Davies1900hLargeLightGreyKnob : Knob {};
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

struct BefacoSliderPot : Slider { // TODO: is using this enum better than two types (Hor/Ver)?
	enum Orientation { Vertical, Horizontal };
	Orientation orientation = Orientation::Vertical;
};
struct CKSSNarrow : Slider {};
struct Crossfader : Slider {};
struct CKSSHoriz2 : Slider {};
struct CKSSVert7 : Slider {};
struct CKSSHoriz4 : Slider {};
struct CKSSNarrow3 : Slider {};
struct BefacoSlidePotSmall : Slider {};

struct Slider25mmVert : Slider {};
struct Slider25mmHoriz : Slider {};

// Input Jacks
struct JackElement : BaseElement {};
struct JackInput : JackElement {};
struct GateJackInput : JackInput {};
struct AnalogJackInput : JackInput {};
struct BefacoInputPort : JackInput {};
using BananutBlack = BefacoInputPort;

// Output jacks
struct JackOutput : JackElement {};
struct GateJackOutput : JackOutput {};
struct AnalogJackOutput : JackOutput {};
struct BefacoOutputPort : JackOutput {};
using BananutRed = BefacoOutputPort;

struct PJ301MPort : JackElement {};

// Displays
struct Display : BaseElement {};
struct BraidsDisplay148x56 : Display {};

// AltParams
struct AltParam : BaseElement {};
struct AltParamToggle2 : AltParam {};
struct AltParamToggle3 : AltParam {};

using Element = std::variant<MediumLight<RedGreenBlueLight>,
							 RedLight,
							 OrangeLight,
							 GreenLight,
							 BlueLight,
							 WhiteLight,
							 RedBlueLight,
							 MomentaryButtonRGB,
							 LatchingButtonMonoLight,
							 Toggle2pos,
							 Toggle3pos,
							 LEDEncoder,
							 Davies1900hBlackKnob,
							 Knob9mm,
							 DaviesLargeKnob,
							 Slider25mmVert,
							 Slider25mmHoriz,
							 Davies1900hRedKnob,
							 Davies1900hWhiteKnob,
							 BefacoTinyKnob,
							 BefacoSliderPot,
							 BefacoTinyKnobWhite,
							 BefacoTinyKnobRed,
							 BefacoTinyKnobDarkGrey,
							 BefacoTinyKnobLightGrey,
							 BefacoTinyKnobBlack,
							 Davies1900hLargeGreyKnob,
							 Davies1900hLightGreyKnob,
							 Davies1900hDarkGreyKnob,
							 Rogan2SGray,
							 Rogan2PSWhite,
							 Rogan2PSGreen,
							 Rogan2PSRed,
							 CKSSNarrow,
							 Crossfader,
							 BefacoSwitchHorizontal,
							 CKSSHoriz2,
							 CKSSVert7,
							 CKSSHoriz4,
							 CKSSNarrow3,
							 Davies1900hLargeLightGreyKnob,
							 BefacoSlidePotSmall,
							 GateJackInput,
							 AnalogJackInput,
							 BefacoInputPort,
							 GateJackOutput,
							 AnalogJackOutput,
							 BefacoOutputPort,
							 PJ301MPort,
							 BraidsDisplay148x56,
							 AltParamToggle2,
							 AltParamToggle3>;

} // namespace MetaModule
