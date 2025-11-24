#include "color_convert.hh"

namespace Handheld
{

Color hsv_to_rgb(float h01, float s01, float v01) {
	// Convert to 8-bit normalized values
	uint16_t h = h01 * 255;
	uint8_t s = s01 * 255;
	uint8_t v = v01 * 255;

	// greyscale
	if (s == 0) {
		return {v, v, v};
	}

	uint8_t region = h / 43;
	uint8_t remainder = (h - (region * 43)) * 6;

	uint8_t p = (v * (255 - s)) >> 8;
	uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	uint8_t r, g, b;
	switch (region) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		default:
			r = v;
			g = p;
			b = q;
			break;
	}

	return {r, g, b};
}

} // namespace Handheld
