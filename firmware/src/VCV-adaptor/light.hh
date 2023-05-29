#pragma once

struct Light {
	float value = 0.f;
	float getBrightness() {
		return value;
	}
	void setBrightness(float value) {
		this->value = value;
	}
	void setSmoothBrightness(float value, float step) { //??? check signature
		setBrightness(value);
	}
};
