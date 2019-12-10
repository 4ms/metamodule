#pragma once
#include <stm32f7xx.h>
#include "controls.hh"

//Todo? Params inherits from Controls? Then we don't need two objects
class Params {
public:
	Params(Controls& c) : controls(c) {}

	float freq[2];
	float res[2];
	uint8_t mode[2] {0};

public:
	void read();
	void update();

private:
	Controls& controls;
};

