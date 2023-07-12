#pragma once

struct NVGcolor {
	union {
		float rgba[4];
		struct {
			float r, g, b, a;
		};
	};
};

inline NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) {
	return {};
}
inline NVGcolor nvgRGBf(float r, float g, float b) {
	return {};
}
inline NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	return {};
};
inline NVGcolor nvgRGBAf(float r, float g, float b, float a) {
	return {};
};
