#pragma once
#include <array>
#include <string_view>
#include <variant>

namespace MetaModule
{

struct BaseElement {
	float x_mm = 0;
	float y_mm = 0;
	// module size is fixed at 128.5mm high x 5.08mm per HP wide

	std::string_view short_name;
	std::string_view long_name;
	unsigned idx = 0;
	float default_val = 0.f;
	float min_val = 0.f;
	float max_val = 1.f;
};

// Lights

struct MonoLight : BaseElement {};
struct RedLight : MonoLight {};
struct OrangeLight : MonoLight {};
struct GreenLight : MonoLight {};
struct BlueLight : MonoLight {};
struct WhiteLight : MonoLight {};

struct DualLight : BaseElement {};
struct RedBlueLight : DualLight {
	enum Color { RED, BLUE };
};

struct RgbLed : BaseElement {
	enum Color { RED, BLUE, GREEN };
};
using RedGreenBlueLight = RgbLed;

template<typename LedT>
struct MediumLight : BaseElement {};

template<>
struct MediumLight<RedGreenBlueLight> : RedGreenBlueLight {};

using LightElement = std::
	variant<MediumLight<RedGreenBlueLight>, RedLight, OrangeLight, GreenLight, BlueLight, WhiteLight, RedBlueLight>;

// Switches/Buttons

struct MomentaryButton : BaseElement {
	enum State { PRESSED, RELEASED };
	enum Color { RED, BLUE, GREEN };
};
struct LatchingButton : BaseElement {
	enum State { PRESSED, RELEASED };
	enum Color { RED, BLUE, GREEN };
};
struct Toggle2pos : BaseElement {};
struct Toggle3pos : BaseElement {};

// Encoders
struct Encoder : BaseElement {};
struct LEDEncoder : BaseElement {
	Encoder encoder;
	RgbLed rgb_led;
};

using SwitchElement = std::variant<MomentaryButton, LatchingButton, Toggle2pos, Toggle3pos, LEDEncoder>;

// Befaco Pots
struct BefacoTinyKnob : BaseElement {};
struct BefacoSliderPot : BaseElement {
	enum Orientation { Vertical, Horizontal };
	Orientation orientation = Orientation::Vertical;
};
struct BefacoTinyKnobWhite : BaseElement {};
struct BefacoTinyKnobRed : BaseElement {};
struct BefacoTinyKnobDarkGrey : BaseElement {};
struct BefacoTinyKnobLightGrey : BaseElement {};
struct BefacoTinyKnobBlack : BaseElement {};
struct Davies1900hLargeGreyKnob : BaseElement {};
struct Davies1900hLightGreyKnob : BaseElement {};
struct Davies1900hDarkGreyKnob : BaseElement {};
struct CKSSNarrow : BaseElement {};
struct Crossfader : BaseElement {};
struct BefacoSwitchHorizontal : BaseElement {};
struct CKSSHoriz2 : BaseElement {};
struct CKSSVert7 : BaseElement {};
struct CKSSHoriz4 : BaseElement {};
struct CKSSNarrow3 : BaseElement {};
struct Davies1900hLargeLightGreyKnob : BaseElement {};
struct BefacoSlidePotSmall : BaseElement {};

// 4ms Pots
struct DaviesLargeKnob : BaseElement {};
struct Davies1900hBlackKnob : BaseElement {};
struct Davies1900hWhiteKnob : BaseElement {};
struct Davies1900hRedKnob : BaseElement {};
struct Knob9mm : BaseElement {};
struct Slider25mmVert : BaseElement {};
struct Slider25mmHoriz : BaseElement {};

using KnobElement = std::variant<
	//4ms
	Davies1900hBlackKnob,
	Knob9mm,
	DaviesLargeKnob,
	Slider25mmVert,
	Slider25mmHoriz,
	// Befaco
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
	CKSSNarrow,
	Crossfader,
	BefacoSwitchHorizontal,
	CKSSHoriz2,
	CKSSVert7,
	CKSSHoriz4,
	CKSSNarrow3,
	Davies1900hLargeLightGreyKnob,
	BefacoSlidePotSmall>;

// Input Jacks
struct JackHexNut : BaseElement {};
struct JackInput : JackHexNut {};
struct GateJackInput : JackInput {};
struct AnalogJackInput : JackInput {};
struct BefacoInputPort : BaseElement {};
using BananutBlack = BefacoInputPort;
using InJackElement = std::variant<GateJackInput, AnalogJackInput, BefacoInputPort>;

// Output jacks
struct JackOutput : JackHexNut {};
struct GateJackOutput : JackOutput {};
struct AnalogJackOutput : JackOutput {};
struct BefacoOutputPort : BaseElement {};
using BananutRed = BefacoOutputPort;
using OutJackElement = std::variant<GateJackOutput, AnalogJackOutput, BefacoOutputPort>;

// AltParams
struct AltParamToggle2 : BaseElement {};
struct AltParamToggle3 : BaseElement {};
using AltParamElement = std::variant<AltParamToggle2, AltParamToggle3>;

struct ElementInfoBase {
	static constexpr std::string_view slug{""};
	static constexpr std::string_view description{""};
	static constexpr uint32_t width_hp = 0;
	static constexpr std::string_view svg_filename{""};
	static constexpr std::array<KnobElement, 0> Knobs{};
	static constexpr std::array<InJackElement, 0> InJacks{};
	static constexpr std::array<OutJackElement, 0> OutJacks{};
	static constexpr std::array<SwitchElement, 0> Switches{};
	static constexpr std::array<LightElement, 0> Leds{};
	static constexpr std::array<AltParamElement, 0> AltParams{};

	template<size_t DPI>
	static constexpr float px_to_mm(float px) {
		constexpr float pix_per_inch = DPI;
		constexpr float mm_per_inch = 25.4f;
		float inches = px / pix_per_inch;
		return inches * mm_per_inch;
	}
};

} // namespace MetaModule
