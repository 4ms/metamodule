#pragma once
#include "leds.h"

struct Version {
	// Version is set here:
	static constexpr uint32_t major_version_digit = 1;
	static constexpr uint32_t minor_version_digit = 0;

	template<uint32_t DIGIT>
	static constexpr Palette version_color() {
		if constexpr (DIGIT == 0)
			return Palette::c_WHITE;
		if constexpr (DIGIT == 1)
			return Palette::c_RED;
		if constexpr (DIGIT == 2)
			return Palette::c_ORANGE;
		if constexpr (DIGIT == 3)
			return Palette::c_YELLOW;
		if constexpr (DIGIT == 4)
			return Palette::c_GREEN;
		if constexpr (DIGIT == 5)
			return Palette::c_BLUE;
		if constexpr (DIGIT == 6)
			return Palette::c_CYAN;
		if constexpr (DIGIT == 7)
			return Palette::c_PURPLE;
		if constexpr (DIGIT == 8)
			return Palette::c_DIMBLUE;
		if constexpr (DIGIT == 9)
			return Palette::c_GREY50;
		return c_OFF;
	}

	static void show_version() {
		set_rgb_led(RgbLeds::LED_PING, version_color<major_version_digit>());
		HAL_Delay(500);
		set_rgb_led(RgbLeds::LED_PING, Palette::c_OFF);
		HAL_Delay(200);
		set_rgb_led(RgbLeds::LED_PING, version_color<minor_version_digit>());
		HAL_Delay(500);
	}
};
