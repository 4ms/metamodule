#include "drivers/stm32xx.h"
#include <cstdint>

namespace MetaModule::System
{

uint32_t get_ticks() {
	return HAL_GetTick();
}

void delay_ms(uint32_t ms) {
	HAL_Delay(ms);
}

} // namespace MetaModule::System
