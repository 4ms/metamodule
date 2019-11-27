#pragma once
#include <stm32f7xx.h>
#include "cap1203.hh"
#include "debug.h"

class TouchCtl {
public:
	TouchCtl() {
		if (sensor_.begin())
			DEBUG0_ON;
		else
			DEBUG0_OFF;
	}

	bool touched(uint8_t padnum) {
		return  padnum==0 ? sensor_.isLeftTouched()  :
				padnum==1 ? sensor_.isRightTouched() :
				padnum==2 ? sensor_.isTouched() : false;
	}
private:
	CAP1203 sensor_;
};