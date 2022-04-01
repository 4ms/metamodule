#pragma once
#include <cstdint>

// required to make sure pin.hh includes these GPIOs
#define GPIOE_BASE static_cast<uint32_t>(FakeGPIO::E)
#define GPIOF_BASE static_cast<uint32_t>(FakeGPIO::F)
#define GPIOG_BASE static_cast<uint32_t>(FakeGPIO::G)
#define GPIOH_BASE static_cast<uint32_t>(FakeGPIO::H)

enum class FakeGPIO : uint32_t {
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
	K,
};
bool read_fake_pin(FakeGPIO port, uint16_t pin_num);
void set_fake_pin(FakeGPIO port, uint16_t pin_num, bool newstate);
