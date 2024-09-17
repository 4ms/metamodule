#pragma once
#include "CoreModules/4ms/4ms_elements.hh"
#include "CoreModules/elements/base_element.hh"
#include "CoreModules/elements/units.hh"
#include "util/colors_rgb565.hh"

namespace MetaModule
{

struct Trimpot : Knob {
	constexpr Trimpot(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Trimpot.png"}}} {
		default_value = defaultValue;
	}
};

struct WhiteMediumKnob : Knob {
	constexpr WhiteMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PWhite.png"}}} {
		default_value = defaultValue;
	}
};

struct WhiteLargeKnob : Knob {
	constexpr WhiteLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PWhite.png"}}} {
		default_value = defaultValue;
	}
};

struct WhiteSmallKnob : Knob {
	constexpr WhiteSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PWhite.png"}}} {
		default_value = defaultValue;
	}
};

struct BlueMediumKnob : Knob {
	constexpr BlueMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PBlue.png"}}} {
		default_value = defaultValue;
	}
};

struct BlueLargeKnob : Knob {
	constexpr BlueLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PBlue.png"}}} {
		default_value = defaultValue;
	}
};

struct BlueSmallKnob : Knob {
	constexpr BlueSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PBlue.png"}}} {
		default_value = defaultValue;
	}
};

struct GreenMediumKnob : Knob {
	constexpr GreenMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PGreen.png"}}} {
		default_value = defaultValue;
	}
};

struct GreenLargeKnob : Knob {
	constexpr GreenLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PGreen.png"}}} {
		default_value = defaultValue;
	}
};

struct GreenSmallKnob : Knob {
	constexpr GreenSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PGreen.png"}}} {
		default_value = defaultValue;
	}
};

struct RedMediumKnob : Knob {
	constexpr RedMediumKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan2PRed.png"}}} {
		default_value = defaultValue;
	}
};

struct RedLargeKnob : Knob {
	constexpr RedLargeKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan3PRed.png"}}} {
		default_value = defaultValue;
	}
};

struct RedSmallKnob : Knob {
	constexpr RedSmallKnob(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan1PRed.png"}}} {
		default_value = defaultValue;
	}
};

struct Rogan6PSWhite : Knob {
	constexpr Rogan6PSWhite(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Rogan6PSWhite.png"}}} {
		default_value = defaultValue;
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

struct RedGreenLight : DualLight {
	constexpr RedGreenLight(BaseElement b)
		: DualLight{{b, "4ms/comp/led_x.png"}, {Colors565::Red, Colors565::Green}} {
	}
};

struct GreenRedLight : DualLight {
	constexpr GreenRedLight(BaseElement b)
		: DualLight{{b, "4ms/comp/led_x.png"}, {Colors565::Green, Colors565::Red}} {
	}
};

struct GreenHandleSlider : Slider {
	constexpr GreenHandleSlider(BaseElement b, float defaultValue = 0.5f)
		: Slider{{{b, "4ms/comp/slider_x.png"}}, "rack-lib/LEDSliderGreenHandle.png"} {
		default_value = defaultValue;
	}
};

struct BraidsDisplay : DynamicTextDisplay {
	constexpr BraidsDisplay(BaseElement b)
		: DynamicTextDisplay{{{b}}} {
		text = "----";
		font = "Segment32";
		color = Colors565::Green;
	}
};

} // namespace MetaModule
