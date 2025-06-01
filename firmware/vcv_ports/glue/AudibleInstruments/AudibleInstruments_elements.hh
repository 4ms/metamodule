#pragma once
#include "CoreModules/elements/base_element.hh"
#include "CoreModules/elements/units.hh"
#include "util/colors_rgb565.hh"

namespace MetaModule
{
namespace
{
constexpr inline void config_knob(Pot &pot,
								  float minValue,
								  float maxValue,
								  float defaultValue,
								  std::string_view unit = "",
								  float displayBase = 0.f,
								  float displayMultiplier = 1.f,
								  float displayOffset = 0.f) {
	pot.min_value = minValue;
	pot.max_value = maxValue;
	auto range = maxValue - minValue;
	pot.default_value = range == 0 ? 0 : (defaultValue - minValue) / range;
	pot.units = unit;
	pot.display_base = displayBase;
	pot.display_mult = displayMultiplier;
	pot.display_offset = displayOffset;
	pot.display_precision = 5;
}
} // namespace

struct Trimpot : Knob {
	constexpr Trimpot(BaseElement b,
					  float min = 0.f,
					  float max = 1.f,
					  float deflt = 0.5f,
					  std::string_view = "",
					  std::string_view unit = "",
					  float disp_base = 0.f,
					  float disp_mult = 1.f,
					  float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Trimpot.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct WhiteMediumKnob : Knob {
	constexpr WhiteMediumKnob(BaseElement b,
							  float min = 0.f,
							  float max = 1.f,
							  float deflt = 0.5f,
							  std::string_view = "",
							  std::string_view unit = "",
							  float disp_base = 0.f,
							  float disp_mult = 1.f,
							  float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan2PWhite.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
	}
};

struct WhiteLargeKnob : Knob {
	constexpr WhiteLargeKnob(BaseElement b,
							 float min = 0.f,
							 float max = 1.f,
							 float deflt = 0.5f,
							 std::string_view = "",
							 std::string_view unit = "",
							 float disp_base = 0.f,
							 float disp_mult = 1.f,
							 float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan3PWhite.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct WhiteSmallKnob : Knob {
	constexpr WhiteSmallKnob(BaseElement b,
							 float min = 0.f,
							 float max = 1.f,
							 float deflt = 0.5f,
							 std::string_view = "",
							 std::string_view unit = "",
							 float disp_base = 0.f,
							 float disp_mult = 1.f,
							 float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan1PWhite.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct BlueMediumKnob : Knob {
	constexpr BlueMediumKnob(BaseElement b,
							 float min = 0.f,
							 float max = 1.f,
							 float deflt = 0.5f,
							 std::string_view = "",
							 std::string_view unit = "",
							 float disp_base = 0.f,
							 float disp_mult = 1.f,
							 float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan2PBlue.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct BlueLargeKnob : Knob {
	constexpr BlueLargeKnob(BaseElement b,
							float min = 0.f,
							float max = 1.f,
							float deflt = 0.5f,
							std::string_view = "",
							std::string_view unit = "",
							float disp_base = 0.f,
							float disp_mult = 1.f,
							float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan3PBlue.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct BlueSmallKnob : Knob {
	constexpr BlueSmallKnob(BaseElement b,
							float min = 0.f,
							float max = 1.f,
							float deflt = 0.5f,
							std::string_view = "",
							std::string_view unit = "",
							float disp_base = 0.f,
							float disp_mult = 1.f,
							float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan1PBlue.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct GreenMediumKnob : Knob {
	constexpr GreenMediumKnob(BaseElement b,
							  float min = 0.f,
							  float max = 1.f,
							  float deflt = 0.5f,
							  std::string_view = "",
							  std::string_view unit = "",
							  float disp_base = 0.f,
							  float disp_mult = 1.f,
							  float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan2PGreen.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct GreenLargeKnob : Knob {
	constexpr GreenLargeKnob(BaseElement b,
							 float min = 0.f,
							 float max = 1.f,
							 float deflt = 0.5f,
							 std::string_view = "",
							 std::string_view unit = "",
							 float disp_base = 0.f,
							 float disp_mult = 1.f,
							 float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan3PGreen.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct GreenSmallKnob : Knob {
	constexpr GreenSmallKnob(BaseElement b,
							 float min = 0.f,
							 float max = 1.f,
							 float deflt = 0.5f,
							 std::string_view = "",
							 std::string_view unit = "",
							 float disp_base = 0.f,
							 float disp_mult = 1.f,
							 float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan1PGreen.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct RedMediumKnob : Knob {
	constexpr RedMediumKnob(BaseElement b,
							float min = 0.f,
							float max = 1.f,
							float deflt = 0.5f,
							std::string_view = "",
							std::string_view unit = "",
							float disp_base = 0.f,
							float disp_mult = 1.f,
							float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan2PRed.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct RedLargeKnob : Knob {
	constexpr RedLargeKnob(BaseElement b,
						   float min = 0.f,
						   float max = 1.f,
						   float deflt = 0.5f,
						   std::string_view = "",
						   std::string_view unit = "",
						   float disp_base = 0.f,
						   float disp_mult = 1.f,
						   float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan3PRed.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct RedSmallKnob : Knob {
	constexpr RedSmallKnob(BaseElement b,
						   float min = 0.f,
						   float max = 1.f,
						   float deflt = 0.5f,
						   std::string_view = "",
						   std::string_view unit = "",
						   float disp_base = 0.f,
						   float disp_mult = 1.f,
						   float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan1PRed.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
	}
};

struct Rogan6PSWhite : Knob {
	constexpr Rogan6PSWhite(BaseElement b,
							float min = 0.f,
							float max = 1.f,
							float deflt = 0.5f,
							std::string_view = "",
							std::string_view unit = "",
							float disp_base = 0.f,
							float disp_mult = 1.f,
							float disp_offset = 0.f)
		: Knob{{{b, "rack-lib/Rogan6PSWhite.png"}}} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
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
	constexpr GreenHandleSlider(BaseElement b,
								float min = 0.f,
								float max = 1.f,
								float deflt = 0.5f,
								std::string_view = "",
								std::string_view unit = "",
								float disp_base = 0.f,
								float disp_mult = 1.f,
								float disp_offset = 0.f)
		: Slider{{{b, "4ms/comp/slider_x.png"}}, "rack-lib/LEDSliderGreenHandle.png"} {
		config_knob(*this, min, max, deflt, unit, disp_base, disp_mult, disp_offset);
		;
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
