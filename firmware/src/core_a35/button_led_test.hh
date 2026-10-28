#pragma once
#include "conf/control_expander_conf.hh"
#include "conf/i2c_conf.hh"
#include "conf/led_driver_conf.hh"
#include "drivers/i2c.hh"
#include "drivers/led_driver_lp5024.hh"
#include "drivers/stm32xx.h"
#include <array>
#include <cstdio>
#include <optional>

// Pro p1 bring-up test for the panel buttons and their RGB LEDs:
// - Prints each button press and release, by name. The buttons are active low (the TCA9555's
//   internal pull-ups), so a button that reads pressed at startup is shorted, e.g. rotated 90
//   degrees. Other expander pins (encoders) that change are printed as raw bits.
// - Cycles all the button LEDs through some colors, and prints each one. A pressed button's LED is
//   white, so that checks the button-to-LED mapping too.
//
// The colors go through ButtonLEDs::rgb_to_outputs() (led_driver_conf.hh), so they should match
// what the console says.
//
// Call start() once, then update() from a loop. Not for the test carrier.

namespace MetaModule
{

struct ButtonLedTest {
	void start() {
		printf("Button/LED test:\n");

		for (auto &led_chip : led_chips) {
			if (!led_chip.init())
				printf("  LP5018 0x%02x: init FAILED\n", led_chip.dev_addr >> 1);
		}

		for (unsigned exp = 0; exp < Controls::Expanders.size(); exp++) {
			readings[exp] = read_expander(exp).value_or(0xFFFF);
		}

		for (unsigned i = 0; i < Controls::Buttons.size(); i++) {
			if (is_pressed(readings, i))
				printf("  %s reads pressed at startup: shorted or installed rotated?\n", ButtonNames[i]);
		}

		next_color_tm = HAL_GetTick();
		next_poll_tm = HAL_GetTick();
	}

	void update() {
		auto now = HAL_GetTick();

		if (int32_t(now - next_color_tm) >= 0) {
			next_color_tm += ColorPeriodMs;
			color_idx = (color_idx + 1) % Colors.size();
			printf("LEDs: %s\n", Colors[color_idx].name);
			for (unsigned led = 0; led < ButtonLEDs::ButtonLeds.size(); led++)
				set_led(led, Colors[color_idx].rgb);
		}

		if (int32_t(now - next_poll_tm) >= 0) {
			next_poll_tm += PollPeriodMs;
			poll_expanders();
		}
	}

private:
	static constexpr uint32_t ColorPeriodMs = 1000;
	static constexpr uint32_t PollPeriodMs = 10;

	struct Color {
		const char *name;
		std::array<uint8_t, 3> rgb;
	};

	static constexpr std::array<Color, 8> Colors{{
		{"red", ButtonLEDs::rgb_to_outputs(0xC0, 0, 0)},
		{"green", ButtonLEDs::rgb_to_outputs(0, 0xC0, 0)},
		{"blue", ButtonLEDs::rgb_to_outputs(0, 0, 0xC0)},
		{"yellow", ButtonLEDs::rgb_to_outputs(0xC0, 0xC0, 0)},
		{"cyan", ButtonLEDs::rgb_to_outputs(0, 0xC0, 0xC0)},
		{"magenta", ButtonLEDs::rgb_to_outputs(0xC0, 0, 0xC0)},
		{"white", ButtonLEDs::rgb_to_outputs(0xC0, 0xC0, 0xC0)},
		{"off", {0, 0, 0}},
	}};

	static constexpr std::array<uint8_t, 3> PressedColor = ButtonLEDs::rgb_to_outputs(0xFF, 0xFF, 0xFF);

	// In Controls::Button order
	static constexpr std::array<const char *, 16> ButtonNames{
		"BUT1", "BUT2", "BUT3", "BUT4", "BUT5", "BUT6", "BUT7", "BUT8",
		"NAV1", "NAV2", "NAV3", "NAV4", "NAV5", "NAV6", "KNOBSET", "PLAY",
	};

	static constexpr std::array<const char *, 4> ExpanderNames{"U1210", "U1211", "U1213", "U1209"};

	mdrivlib::I2CPeriph controls_a_i2c{controls_a_i2c_conf};
	mdrivlib::I2CPeriph controls_b_i2c{controls_b_i2c_conf};
	mdrivlib::I2CPeriph led_i2c{led_i2c_conf};

	std::array<mdrivlib::LP5024::Device, 2> led_chips{{
		{led_i2c, ButtonLEDs::led_chip_addr_8bit(0)},
		{led_i2c, ButtonLEDs::led_chip_addr_8bit(1)},
	}};

	std::array<uint16_t, 4> readings{};
	std::array<bool, 4> read_failed{};
	unsigned color_idx = 0;
	uint32_t next_color_tm = 0;
	uint32_t next_poll_tm = 0;

	mdrivlib::I2CPeriph &bus(unsigned exp) {
		return Controls::Expanders[exp].bus == Controls::ExpanderConf::Bus::ControlsA ? controls_a_i2c : controls_b_i2c;
	}

	std::optional<uint16_t> read_expander(unsigned exp) {
		std::array<uint8_t, 2> inputs{};
		auto addr = Controls::Expanders[exp].chip.addr << 1;
		if (bus(exp).mem_read(addr, 0x00, 1, inputs.data(), inputs.size()) != mdrivlib::I2CPeriph::I2C_NO_ERR)
			return std::nullopt;
		return (inputs[1] << 8) | inputs[0];
	}

	static bool is_pressed(std::array<uint16_t, 4> const &readings, unsigned button) {
		auto b = Controls::Buttons[button];
		return (readings[b.exp] & (1 << b.bit)) == 0;
	}

	// ButtonLeds skips the NAV buttons
	static std::optional<unsigned> led_of_button(unsigned button) {
		using enum Controls::Button;
		if (button <= unsigned(But8))
			return button;
		if (button == unsigned(Knobset))
			return 8;
		if (button == unsigned(Play))
			return 9;
		return std::nullopt;
	}

	void set_led(unsigned led, std::array<uint8_t, 3> const &rgb) {
		auto [chip, rgb_led_id] = ButtonLEDs::ButtonLeds[led];
		led_chips[chip].set_rgb_led(rgb_led_id, rgb);
	}

	void poll_expanders() {
		auto prev = readings;

		for (unsigned exp = 0; exp < readings.size(); exp++) {
			auto reading = read_expander(exp);
			if (!reading) {
				if (!read_failed[exp])
					printf("%s: read FAILED\n", ExpanderNames[exp]);
				read_failed[exp] = true;
				continue;
			}
			read_failed[exp] = false;
			readings[exp] = *reading;
		}

		std::array<uint16_t, 4> button_bits{};

		for (unsigned i = 0; i < Controls::Buttons.size(); i++) {
			auto b = Controls::Buttons[i];
			button_bits[b.exp] |= 1 << b.bit;

			bool pressed = is_pressed(readings, i);
			if (pressed == is_pressed(prev, i))
				continue;

			printf("%s %s\n", ButtonNames[i], pressed ? "pressed" : "released");
			if (auto led = led_of_button(i))
				set_led(*led, pressed ? PressedColor : Colors[color_idx].rgb);
		}

		// Everything else: the encoders
		for (unsigned exp = 0; exp < readings.size(); exp++) {
			uint16_t changed = (readings[exp] ^ prev[exp]) & ~button_bits[exp];
			for (unsigned bit = 0; bit < 16; bit++) {
				if (changed & (1 << bit))
					printf("%s P%u%u = %u\n", ExpanderNames[exp], bit / 8, bit % 8, (readings[exp] >> bit) & 1);
			}
		}
	}
};

} // namespace MetaModule
