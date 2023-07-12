#pragma once

struct NVGcolor {
	union {
		float rgba[4];
		struct {
			float r, g, b, a;
		};
	};
};

NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) {
	return {};
}
NVGcolor nvgRGBf(float r, float g, float b) {
	return {};
}
NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	return {};
};
NVGcolor nvgRGBAf(float r, float g, float b, float a) {
	return {};
};
