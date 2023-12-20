#include "drivers/stm32xx.h"

inline void delay_ms(uint32_t ms) {
	HAL_Delay(ms);
}
