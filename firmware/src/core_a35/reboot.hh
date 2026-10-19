#pragma once
#include "drivers/stm32xx.h"

// MP2 version of src/core_a7/reboot.hh
inline void reboot_system() {
	RCC->GRSTCSETR = RCC_GRSTCSETR_SYSRST;
}
