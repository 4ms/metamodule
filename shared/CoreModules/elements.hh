#pragma once
#include <array>
#include <span>
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
struct LEDEncoder : Encoder {
	Encoder encoder;
	RgbLed rgb_led;
};

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
using InJackElement = std::variant<GateJackInput, AnalogJackInput, BefacoInputPort>;

// Output jacks
struct JackOutput : JackElement {};
struct GateJackOutput : JackOutput {};
struct AnalogJackOutput : JackOutput {};
struct BefacoOutputPort : JackOutput {};
using BananutRed = BefacoOutputPort;
using OutJackElement = std::variant<GateJackOutput, AnalogJackOutput, BefacoOutputPort>;

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

struct ElementInfoBase {
	static constexpr std::string_view slug{""};
	static constexpr std::string_view description{""};
	static constexpr uint32_t width_hp = 0;
	static constexpr std::string_view svg_filename{""};
	static constexpr std::array<Element, 0> Elements{};

	template<size_t DPI>
	static constexpr float px_to_mm(float px) {
		constexpr float pix_per_inch = DPI;
		constexpr float mm_per_inch = 25.4f;
		float inches = px / pix_per_inch;
		return inches * mm_per_inch;
	}

	// mm: length or position in mm
	// pixels_per_3U: the module height in pixels
	static constexpr float mm_to_px(float mm, uint32_t pixels_per_3U) {
		constexpr float mm_per_3U = 128.5f; //standard Eurorack size
		float pixels_per_mm = pixels_per_3U / mm_per_3U;
		return mm * pixels_per_mm;
	}

	static constexpr float to_mm(float vcv_px) {
		constexpr float svg_dpi = 75.f; // As found in common SVG files in Rack repo
		constexpr float mm_per_px = 25.4f / svg_dpi;

		return vcv_px * mm_per_px;
	}
};

#ifndef VCVRACK
#ifndef ENUMS
#define ENUMS(name, count) name, name##_LAST = name + (count)-1
#endif
#endif

} // namespace MetaModule
