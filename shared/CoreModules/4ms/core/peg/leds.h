/*
 * leds.h
 */

#pragma once

#include "pwm.h"
#include <stdint.h>

enum RgbLeds {
	LED_PING,
	LED_CYCLE,
	LED_ENVA,
	LED_ENVB,

	NUM_RGB_LEDS
};

enum MonoLeds {
	LED_TRIGOUT,

	NUM_MONO_LEDS
};

struct Color {
	uint16_t r;
	uint16_t g;
	uint16_t b;
};

struct AdjustedColor {
	Color ping;
	Color cycle;
	Color envA;
	Color envB;
};

enum Palette {
	c_OFF,
	c_GREY50,
	c_WHITE,
	c_FULLWHITE,
	c_RED,
	c_ORANGE,
	c_YELLOW,
	c_GREEN,
	c_CYAN,
	c_BLUE,
	c_DIMBLUE,
	c_PURPLE,

	NUM_COLORS
};

constexpr inline uint32_t kMaxBrightness = 4095;
constexpr inline uint32_t kMaxBrightnessBits = 12;

void set_led_brightness(uint16_t brightness, PwmOutputs pwm_led_num);
void set_rgb_led(RgbLeds rgb_led_id, Palette color_id);
void adjust_palette(void);
uint16_t adjust_hue(uint16_t base, uint16_t adj);
void all_lights_off(void);
