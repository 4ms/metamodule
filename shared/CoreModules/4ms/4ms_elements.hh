#pragma once
#include "CoreModules/elements/base_element.hh"
#include "CoreModules/elements/units.hh"
#include "util/colors_rgb565.hh"

namespace MetaModule
{

//
// Knobs
//
struct Knob9mm : Knob {
	constexpr Knob9mm() = default;
	constexpr Knob9mm(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "4ms/comp/knob9mm_x.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct DaviesLargeKnob : Knob {
	constexpr DaviesLargeKnob() = default;
	constexpr DaviesLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "4ms/comp/knob_large_x.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct Davies1900hBlackKnob : Knob {
	constexpr Davies1900hBlackKnob() = default;
	constexpr Davies1900hBlackKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "4ms/comp/knob_x.png"}}} {
		DefaultValue = defaultValue;
	}
};

// AI:
struct WhiteMediumKnob : Knob {
	constexpr WhiteMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PWhite.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct WhiteLargeKnob : Knob {
	constexpr WhiteLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PWhite.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct WhiteSmallKnob : Knob {
	constexpr WhiteSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Trimpot.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct BlueMediumKnob : Knob {
	constexpr BlueMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PBlue.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct BlueLargeKnob : Knob {
	constexpr BlueLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PBlue.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct BlueSmallKnob : Knob {
	constexpr BlueSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PBlue.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct GreenMediumKnob : Knob {
	constexpr GreenMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PGreen.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct GreenLargeKnob : Knob {
	constexpr GreenLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PGreen.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct GreenSmallKnob : Knob {
	constexpr GreenSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PGreen.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct RedMediumKnob : Knob {
	constexpr RedMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PRed.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct RedLargeKnob : Knob {
	constexpr RedLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PRed.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct RedSmallKnob : Knob {
	constexpr RedSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PRed.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct Rogan6PSWhite : Knob {
	constexpr Rogan6PSWhite(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan6PSWhite.png"}}} {
		DefaultValue = defaultValue;
	}
};

struct Rogan6PSLight : RgbLight {
	constexpr Rogan6PSLight(BaseElement b)
		: RgbLight{{{b, "rack-lib/Rogan6PSLight.png"}}} {
		width_mm = to_mm<72>(44);
		height_mm = width_mm;
	}
};

struct SmallButton : MomentaryButton {
	constexpr SmallButton(BaseElement b)
		: MomentaryButton{{b}} {
		image = "rack-lib/TL1105_0.png";
		pressed_image = "rack-lib/TL1105_1.png";
	}
};

struct MediumButton : MomentaryButton {
	constexpr MediumButton(BaseElement b)
		: MomentaryButton{{b}} {
		image = "rack-lib/CKD6_0.png";
		pressed_image = "rack-lib/CKD6_1.png";
	}
};

//
// Sliders
//
struct Slider25mmHorizLED : SliderLight {
	constexpr Slider25mmHorizLED() = default;
	constexpr Slider25mmHorizLED(BaseElement b, float defaultValue = 0.5f)
		: SliderLight{{{{b, "4ms/comp/slider_horiz_x.png"}}, "4ms/comp/slider_horiz_handle_x.png"}, Colors565::White} {
		DefaultValue = defaultValue;
	}
};

struct Slider25mmVertLED : SliderLight {
	constexpr Slider25mmVertLED() = default;
	constexpr Slider25mmVertLED(BaseElement b, float defaultValue = 0.5f)
		: SliderLight{{{{b, "4ms/comp/slider_x.png"}}, "4ms/comp/slider_handle_x.png"}, Colors565::White} {
		DefaultValue = defaultValue;
	}
};

//
// Buttons
//
struct OrangeButton : LatchingButton {
	constexpr OrangeButton(BaseElement b, State_t defaultValue = State_t::UP)
		: LatchingButton{{b, "4ms/comp/button_x.png"}, defaultValue, Colors565::Orange} {
	}
};

struct WhiteMomentary7mm : MomentaryButtonLight {
	constexpr WhiteMomentary7mm() = default;
	constexpr WhiteMomentary7mm(BaseElement b)
		: MomentaryButtonLight{{{b, "4ms/comp/button_x.png"}, ""}, Colors565::White} {
	}
};

struct MomentaryRGB7mm : MomentaryButtonRGB {
	constexpr MomentaryRGB7mm() = default;
	constexpr MomentaryRGB7mm(BaseElement b)
		: MomentaryButtonRGB{{{b, "4ms/comp/button_x.png"}, ""}} {
	}
};

struct MomentaryRGB5mm : MomentaryButtonRGB {
	constexpr MomentaryRGB5mm() = default;
	constexpr MomentaryRGB5mm(BaseElement b)
		: MomentaryButtonRGB{{{b, "4ms/comp/button_x.png"}, ""}} {
	}
};

//
// Switches
//
struct Toggle2pos : FlipSwitch {
	enum State_t : FlipSwitch::State_t { DOWN = 0, UP = 1 };

	constexpr Toggle2pos() = default;
	constexpr Toggle2pos(BaseElement b,
						 std::array<std::string_view, 2> names = {"Down", "Up"},
						 State_t defaultValue = State_t::DOWN)
		: FlipSwitch{
			  {{b}, 2, defaultValue},
			  {"4ms/comp/switch_down.png", "4ms/comp/switch_up.png"},
			  {names[0], names[1]},
		  } {
	}
};

struct Toggle3pos : FlipSwitch {
	enum State_t : FlipSwitch::State_t { DOWN = 0, CENTER = 1, UP = 2 };

	constexpr Toggle3pos() = default;
	constexpr Toggle3pos(BaseElement b,
						 std::array<std::string_view, 3> names = {"Down", "Center", "Up"},
						 State_t defaultValue = State_t::DOWN)
		: FlipSwitch{
			  {{b}, 3, defaultValue},
			  {"4ms/comp/switch_down.png", "4ms/comp/switch_center.png", "4ms/comp/switch_up.png"},
			  {names[0], names[1], names[2]},
		  } {
	}
};

struct Toggle2posHoriz : FlipSwitch {
	enum State_t : FlipSwitch::State_t { LEFT = 0, RIGHT = 1 };

	constexpr Toggle2posHoriz() = default;
	constexpr Toggle2posHoriz(BaseElement b,
							  std::array<std::string_view, 2> names = {"Left", "Right"},
							  State_t defaultValue = State_t::LEFT)
		: FlipSwitch{
			  {{b}, 2, defaultValue},
			  {"4ms/comp/switch_horiz_left.png", "4ms/comp/switch_horiz_right.png"},
			  {names[0], names[1]},
		  } {
	}
};

struct Toggle3posHoriz : FlipSwitch {
	enum State_t : FlipSwitch::State_t { LEFT = 0, CENTER = 1, RIGHT = 2 };

	constexpr Toggle3posHoriz() = default;
	constexpr Toggle3posHoriz(BaseElement b,
							  std::array<std::string_view, 3> names = {"Left", "Center", "Right"},
							  State_t defaultValue = State_t::LEFT)
		: FlipSwitch{
			  {{b}, 3, defaultValue},
			  {"4ms/comp/switch_horiz_left.png", "4ms/comp/switch_horiz_center.png", "4ms/comp/switch_horiz_right.png"},
			  {names[0], names[1], names[2]},
		  } {
	}
};

struct Encoder9mmRGB : EncoderRGB {
	constexpr Encoder9mmRGB(BaseElement b)
		: EncoderRGB{b, "4ms/comp/knob_unlined_x.png"} {
	}
};

//
// Input Jacks
//

struct GateJackInput4ms : JackInput {
	constexpr GateJackInput4ms(BaseElement b)
		: JackInput{b, "4ms/comp/jack_x.png"} {
	}
};
struct AnalogJackInput4ms : JackInput {
	constexpr AnalogJackInput4ms(BaseElement b)
		: JackInput{b, "4ms/comp/jack_x.png"} {
	}
};

//
// Output jacks
//

struct GateJackOutput4ms : JackOutput {
	constexpr GateJackOutput4ms(BaseElement b)
		: JackOutput{b, "4ms/comp/jack_x.png"} {
	}
};
struct AnalogJackOutput4ms : JackOutput {
	constexpr AnalogJackOutput4ms(BaseElement b)
		: JackOutput{b, "4ms/comp/jack_x.png"} {
	}
};

//
// Lights
//

struct RedLight : MonoLight {
	constexpr RedLight(BaseElement b)
		: MonoLight{{b, "4ms/comp/led_x.png"}, Colors565::Red} {
	}
};

struct BlueLight : MonoLight {
	constexpr BlueLight(BaseElement b)
		: MonoLight{{b, "4ms/comp/led_x.png"}, Colors565::Blue} {
	}
};

struct WhiteLight : MonoLight {
	constexpr WhiteLight(BaseElement b)
		: MonoLight{{b, "4ms/comp/led_x.png"}, Colors565::White} {
	}
};

struct GreenLight : MonoLight {
	constexpr GreenLight(BaseElement b)
		: MonoLight{{b, "4ms/comp/led_x.png"}, Colors565::Green} {
	}
};

struct YellowLight : MonoLight {
	constexpr YellowLight(BaseElement b)
		: MonoLight{{b, "4ms/comp/led_x.png"}, Colors565::Yellow} {
	}
};

struct OrangeLight : MonoLight {
	constexpr OrangeLight(BaseElement b)
		: MonoLight{{b, "4ms/comp/led_x.png"}, Colors565::Orange} {
	}
};

struct RedBlueLight : DualLight {
	constexpr RedBlueLight(BaseElement b)
		: DualLight{{b, "4ms/comp/led_x.png"}, {Colors565::Red, Colors565::Blue}} {
	}
};

struct RedGreenLight : DualLight {
	constexpr RedGreenLight(BaseElement b)
		: DualLight{{b, "4ms/comp/led_x.png"}, {Colors565::Red, Colors565::Green}} {
	}
};

struct RedGreenBlueLight : RgbLight {
	constexpr RedGreenBlueLight(BaseElement b)
		: RgbLight{{b, "4ms/comp/led_x.png"}} {
	}
};

} // namespace MetaModule
