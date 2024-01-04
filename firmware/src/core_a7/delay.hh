#include "drivers/stm32xx.h"

inline uint64_t get_time() {
	return HAL_GetTick();
}

inline void delay_ms(uint32_t ms) {
	HAL_Delay(ms);
}
