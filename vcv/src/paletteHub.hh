#pragma once
#include <rack.hpp>

struct PaletteHub {
	static inline const NVGcolor ORANGE = nvgRGB(0xff, 0x80, 0x00);
	static inline const NVGcolor BROWN = nvgRGB(0x80, 0x40, 0x00);

	static inline const NVGcolor BLACK = nvgRGB(0x00, 0x00, 0x00);
	static inline const NVGcolor RED = nvgRGB(0xff, 0x00, 0x00);
	static inline const NVGcolor GREEN = nvgRGB(0x00, 0xff, 0x00);
	static inline const NVGcolor BLUE = nvgRGB(0x00, 0x00, 0xff);
	static inline const NVGcolor CYAN = nvgRGB(0x00, 0xff, 0xff);
	static inline const NVGcolor MAGENTA = nvgRGB(0xff, 0x00, 0xff);
	static inline const NVGcolor YELLOW = nvgRGB(0xff, 0xff, 0x00);
	static inline const NVGcolor WHITE = nvgRGB(0xff, 0xff, 0xff);

	static inline const NVGcolor color[8] = {
		BLACK,
		BROWN,
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		BLUE,
		MAGENTA,
	};
};
