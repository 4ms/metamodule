#pragma once
#include "pin.hh"

struct QSPIFlashConfig {
	PinNoInit io0;
	PinNoInit io1;
	PinNoInit io2;
	PinNoInit io3;
	PinNoInit clk;
	PinNoInit cs;
};

