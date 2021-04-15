#pragma once
#include <stdint.h>

enum class FakeGPIO : uint8_t {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K
};
bool read_fake_pin(FakeGPIO port, uint16_t pin_num);
void set_fake_pin(FakeGPIO port, uint16_t pin_num, bool newstate);
