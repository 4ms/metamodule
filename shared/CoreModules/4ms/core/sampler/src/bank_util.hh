#pragma once

#include <cstdint>

namespace SamplerKit
{

// Given a bank number, sets color to the default bank name
// Example: 49 ==> Pearl-4
uint8_t bank_to_color(uint8_t bank, char *color);

// Given a color string, return a bank number.
// If the color string doesn't match any default bank names,
// return MaxNumBanks
uint8_t color_to_bank(const char *color);

// Given a number, returns the units digit
// This digit refers to the bank color, regardless of blink #
inline uint8_t get_bank_color_digit(uint8_t bank) {
	if (bank < 10)
		return bank;

	while (bank >= 10)
		bank -= 10;
	return (bank);
}

// Given a number, returns the tens digit
// This digit refers to the bank blink #, regardless of color
inline uint8_t get_bank_blink_digit(uint8_t bank) { return (bank / 10); }

} // namespace SamplerKit
