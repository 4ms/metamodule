#pragma once
#include <stm32f7xx.h>
#include "controls.hh"

class Params {
public:
	float freq[2];
	float res[2];

public:
	void read(Controls& controls);
	void update(Controls& controls);
};

