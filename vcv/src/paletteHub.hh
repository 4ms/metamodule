#include <rack.hpp>

struct PaletteHub {
	static inline const NVGcolor ORANGE = nvgRGB(0xff, 0x80, 0x00);
	static inline const NVGcolor BROWN = nvgRGB(0x80, 0x40, 0x00);

	static inline const NVGcolor color[8] = {
		rack::color::BLACK,
		BROWN,
		rack::color::RED,
		ORANGE,
		rack::color::YELLOW,
		rack::color::GREEN,
		rack::color::BLUE,
		rack::color::MAGENTA,
	};
};