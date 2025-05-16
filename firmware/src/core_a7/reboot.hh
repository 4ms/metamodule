#pragma once
#include "stm32mp1xx.h"

inline void reboot_system() {
	__HAL_RCC_SYS_RESET();
}
