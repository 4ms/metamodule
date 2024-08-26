#pragma once
#include "util/debouncer.hh"
#include "util/rgbled.hh"
#include <cstdint>
#include <limits>

namespace SamplerKit::Mocks
{

struct TrigIn : public Debouncer<0b0001, 0b1110, 0b1111> {
	void update() {
	}
};

struct Button : public DebouncerCounter<0b01, 0b10, 0b11> {
	void update() {
	}

	void sideload_set(bool newVal) {
		register_state(newVal);
	}

	unsigned how_long_held() {
		return steady_state_ctr;
	}

	unsigned how_long_held_pressed() {
		return is_pressed() ? steady_state_ctr : 0;
	}

	void reset_hold_ctr() {
		steady_state_ctr = 0;
	}
};

struct OutputPin {
	void set(bool val) {
		if (val)
			high();
		else
			low();
	}

	void low() {
		value = false;
	}

	void high() {
		value = true;
	}

	bool sideload_get() const {
		return value;
	}

private:
	bool value;
};

struct LED : OutputPin {};
struct TrigOut : OutputPin {};

struct LedElement {
	uint8_t &val;

	LedElement(uint8_t &data)
		: val{data} {
	}

	void set(uint8_t v) const {
		val = v;
	}
};

using RgbLed = MixedRgbLed<LedElement, LedElement, LedElement>;

} // namespace SamplerKit::Mocks
