#pragma once

#include "button_led.hh"

namespace MetaModule
{

struct ButtonLight {

	struct Colors {
		static constexpr Color off = Color(0, 0, 0);
		static constexpr Color black = Color(0, 0, 0);
		static constexpr Color grey = Color(92, 49, 72);
		static constexpr Color white = Color(255, 145, 218);

		static constexpr Color red = Color(188, 0, 0);
		static constexpr Color orange = Color(188, 37, 0);
		static constexpr Color yellow = Color(155, 91, 0);
		static constexpr Color green = Color(0, 131, 0);
		static constexpr Color cyan = Color(0, 130, 130);
		static constexpr Color blue = Color(0, 0, 175);
		static constexpr Color purple = Color(80, 0, 170);

		static constexpr Color magenta = Color(200, 0, 200);
		static constexpr Color pink = Color(255, 20, 100);
		static constexpr Color pale_pink = Color(255, 34, 122);
	};

	static constexpr std::array<Color, 8> KnobSetColors{
		Colors::white,
		Colors::red,
		Colors::orange,
		Colors::yellow,
		Colors::green,
		Colors::cyan,
		Colors::blue,
		Colors::purple,
	};

	void display_knobset(unsigned knobset_id) {
		if (knobset_id < KnobSetColors.size())
			led.set_color(KnobSetColors[knobset_id]);
	}

	void debug(float r, float g, float b) {
		led.set_color(Color(255.f * r, 255.f * g, 255.f * b));
	}

	ButtonLED led;
};

} // namespace MetaModule
