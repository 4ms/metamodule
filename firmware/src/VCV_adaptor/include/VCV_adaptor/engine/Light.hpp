#pragma once
#include "VCV_adaptor/common.hpp"

namespace rack::engine
{

struct Light {
	float value = 0.f;
	void setBrightness(float brightness) {
		value = brightness;
	}

	float getBrightness() {
		return value;
	}

	void setBrightnessSmooth(float brightness, float deltaTime, float lambda = 30.f) {
		if (brightness < value) {
			// Fade out light
			value += (brightness - value) * lambda * deltaTime;
		} else {
			// Immediately illuminate light
			value = brightness;
		}
	}

	void setSmoothBrightness(float brightness, float deltaTime) {
		setBrightnessSmooth(brightness, deltaTime);
	}

	DEPRECATED void setBrightnessSmooth(float brightness, int frames = 1) {
		setBrightnessSmooth(brightness, frames / 44100.f);
	}
};

} // namespace rack::engine
