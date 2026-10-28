#pragma once
#include <array>
#include <cstdint>

// RGB button LEDs: two LP5018 on I2C6 (see led_i2c_conf in i2c_conf.hh).
// The LP5018 has the same register map as the LP5024 (it only has LED0-5 / OUT0-17),
// so use mdrivlib::LP5024::Device. That driver takes the 8-bit (shifted) I2C address.

namespace MetaModule::ButtonLEDs
{

constexpr uint8_t LedChipAddr7bit[2] = {
	0x28, // U5: ADDR1=0, ADDR0=0
	0x29, // U8: ADDR1=0, ADDR0=1
};

constexpr uint8_t led_chip_addr_8bit(unsigned chip) {
	return LedChipAddr7bit[chip] << 1;
}

// Each RGB LED is three consecutive outputs, so it is addressed as
// rgb_led_id = first output / 3 in LP5024::Device::set_rgb_led()
//
// The outputs are in R, B, G order: the schematic's LED_BUTn_G and LED_BUTn_B net names are
// swapped (the button's pin 7 is B and pin 6 is G, as its symbol's pin names say). Verified on p1.
// So use rgb_to_outputs() for the values passed to set_rgb_led().
constexpr std::array<uint8_t, 3> rgb_to_outputs(uint8_t r, uint8_t g, uint8_t b) {
	return {r, b, g};
}

struct RgbLed {
	uint8_t chip;
	uint8_t rgb_led_id;
};

// RGB LED buttons SW101..SW110. Their LED nets are named LED_BUT1..10; the switches
// are BUT1..BUT8 (SW101..SW108), KNOBSET (SW109), and PLAY (SW110).
// Indexed in the same order as Controls::Button (control_expander_conf.hh),
// skipping the six NAV buttons, which have no LEDs.
// clang-format off
constexpr std::array<RgbLed, 10> ButtonLeds{{
	/* BUT1  */ {0, 3},
	/* BUT2  */ {0, 2},
	/* BUT3  */ {0, 1},
	/* BUT4  */ {0, 0},
	/* BUT5  */ {1, 4},
	/* BUT6  */ {1, 3},
	/* BUT7  */ {1, 2},
	/* BUT8  */ {1, 1},
	/* KNOBSET (LED_BUT9)  */ {0, 4},
	/* PLAY    (LED_BUT10) */ {1, 0},
}};
// clang-format on

} // namespace MetaModule::ButtonLEDs
