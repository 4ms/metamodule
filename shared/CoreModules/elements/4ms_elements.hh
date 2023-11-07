#pragma once
#include "base_element.hh"

namespace MetaModule
{

using Color565 = uint16_t;

//
// Knobs
//
struct Knob9mm : Knob {
	constexpr Knob9mm() = default;
	constexpr Knob9mm(BaseElement b)
		: Knob{{b}, "knob9mm_x.png"} {
	}
};

struct DaviesLargeKnob : Knob {
	constexpr DaviesLargeKnob() = default;
	constexpr DaviesLargeKnob(BaseElement b)
		: Knob{{b}, "knob_large_x.png"} {
	}
};

struct Davies1900hBlackKnob : Knob {
	constexpr Davies1900hBlackKnob() = default;
	constexpr Davies1900hBlackKnob(BaseElement b)
		: Knob{{b}, "knob_x.png"} {
	}
};

//
// Sliders
//
struct Slider25mmHorizLED : SliderLight {
	constexpr Slider25mmHorizLED() = default;
	constexpr Slider25mmHorizLED(BaseElement b)
		: SliderLight{{{b}, "slider_x.png"}, 0xFFFF} {
	}
};

struct Slider25mmVertLED : SliderLight {
	constexpr Slider25mmVertLED() = default;
	constexpr Slider25mmVertLED(BaseElement b)
		: SliderLight{{{b}, "slider_x.png"}, 0xFFFF} {
	}
};

//
// Buttons
//
struct OrangeButton : LatchingButton {
	constexpr OrangeButton(BaseElement b)
		: LatchingButton{{{b}, "button_x.png"}, 0xfd40} {
	}
};

struct WhiteMomentary7mm : MomentaryButtonWhiteLight {
	constexpr WhiteMomentary7mm() = default;
	constexpr WhiteMomentary7mm(BaseElement b)
		: MomentaryButtonWhiteLight{{{{b}, "button_x.png"}}} {
	}
};

struct MomentaryRGB7mm : MomentaryButtonRGB {
	constexpr MomentaryRGB7mm() = default;
	constexpr MomentaryRGB7mm(BaseElement b)
		: MomentaryButtonRGB{{{{b}, "button_x.png"}}} {
	}
};

struct MomentaryRGB5mm : MomentaryButtonRGB {
	constexpr MomentaryRGB5mm() = default;
	constexpr MomentaryRGB5mm(BaseElement b)
		: MomentaryButtonRGB{{{{b}, "button_x.png"}}} {
	}
};

//
// Switches
//
struct Toggle2pos : FlipSwitch {
	enum State_t : FlipSwitch::State_t { DOWN = 0, UP = 1 };

	constexpr Toggle2pos() = default;
	constexpr Toggle2pos(BaseElement b)
		: FlipSwitch{{b}, 2, {"switch_down.png", "switch_up.png"}} {
	}
	constexpr Toggle2pos(BaseElement b, std::array<std::string_view, 2> names)
		: FlipSwitch{{b}, 2, {"switch_down.png", "switch_up.png"}, {names[0], names[1]}} {
	}
};

struct Toggle3pos : FlipSwitch {
	enum State_t : FlipSwitch::State_t { DOWN = 0, CENTER = 1, UP = 2 };

	constexpr Toggle3pos() = default;
	constexpr Toggle3pos(BaseElement b)
		: FlipSwitch{{b}, 3, {"switch_down.png", "switch_center.png", "switch_up.png"}} {
	}
	constexpr Toggle3pos(BaseElement b, std::array<std::string_view, 3> names)
		: FlipSwitch{
			  {b}, 3, {"switch_down.png", "switch_center.png", "switch_up.png"}, {names[0], names[1], names[2]}} {
	}
};

struct Toggle2posHoriz : FlipSwitch {
	enum State_t : FlipSwitch::State_t { DOWN = 0, UP = 1 };

	constexpr Toggle2posHoriz() = default;
	constexpr Toggle2posHoriz(BaseElement b)
		: FlipSwitch{{b}, 2, {"switch_horiz_down.png", "switch_horiz_up.png"}} {
	}
	constexpr Toggle2posHoriz(BaseElement b, std::array<std::string_view, 2> names)
		: FlipSwitch{{b}, 2, {"switch_horiz_down.png", "switch_horiz_up.png"}, {names[0], names[1]}} {
	}
};

struct Toggle3posHoriz : FlipSwitch {
	enum State_t : FlipSwitch::State_t { DOWN = 0, CENTER = 1, UP = 2 };

	constexpr Toggle3posHoriz() = default;
	constexpr Toggle3posHoriz(BaseElement b)
		: FlipSwitch{{b}, 3, {"switch_horiz_down.png", "switch_horiz_center.png", "switch_horiz_up.png"}} {
	}
	constexpr Toggle3posHoriz(BaseElement b, std::array<std::string_view, 3> names)
		: FlipSwitch{{b},
					 3,
					 {"switch_horiz_down.png", "switch_horiz_center.png", "switch_horiz_up.png"},
					 {names[0], names[1], names[2]}} {
	}
};

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
