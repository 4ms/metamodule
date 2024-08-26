#include "bank_util.hh"
#include "elements.hh"
#include "str_util.h"

namespace SamplerKit
{

static uint8_t bank_to_color_string(uint8_t bank, char *color) {
	switch (bank) {
		case 0:
			str_cpy(color, "White");
			return 5;
			break;

		case 1:
			str_cpy(color, "Red");
			return 3;
			break;

		case 2:
			str_cpy(color, "Orange");
			return 6;
			break;

		case 3:
			str_cpy(color, "Yellow");
			return 6;
			break;

		case 4:
			str_cpy(color, "Green");
			return 5;
			break;

		case 5:
			str_cpy(color, "Cyan");
			return 4;
			break;

		case 6:
			str_cpy(color, "Blue");
			return 4;
			break;

		case 7:
			str_cpy(color, "Magenta");
			return 7;
			break;

		case 8:
			str_cpy(color, "Lavender");
			return 8;
			break;

		case 9:
			str_cpy(color, "Pearl");
			return 5;
			break;

		default:
			color[0] = 0;
			return 0;
	}
}

// Given a bank number, sets color to the default bank name
// Example: 49 ==> Pearl-4
uint8_t bank_to_color(uint8_t bank, char *color) {
	uint8_t digit1, digit2, len;

	if (bank > 9 && bank < 100) {
		// convert a 2-digit bank number to a color and number

		// First digit: 49 ---> 4
		digit1 = bank / 10;

		// Second digit: 49 ---> (49 - 4*10) = 9
		digit2 = bank - (digit1 * 10);

		// Second digit as a color string i.e. "White" etc
		len = bank_to_color_string(digit2, color);

		// Omit the "0" for the first bank of a color, so "Red-0" is just "Red"
		// Otherwise append a dash and number to the color name
		if (digit1 > 0) {
			// Move pointer to the end of the string (overwrite the \0)
			color += len;

			// Append a dash: "White-"
			*color++ = '-';
			len++;

			// Append first digit as a string: "White-5"
			intToStr(digit1, color, 1);
			len++;
		}

		return (len);
	} else
		return bank_to_color_string(bank, color);
}

// Given a color string, return a bank number.
// If the color string doesn't match any default bank names,
// return MaxNumBanks
uint8_t color_to_bank(const char *color) {
	uint8_t i;
	char b_color[11];

	// for every bank number
	for (i = 0; i < MaxNumBanks; i++) {
		// convert bank number to color
		bank_to_color(i, b_color);

		// compare current bank color with input bank color
		if (str_cmp_nocase(color, b_color)) {
			// ... and return bank number if there's a match
			return i;
		}
	}
	return MaxNumBanks;
}

} // namespace SamplerKit
