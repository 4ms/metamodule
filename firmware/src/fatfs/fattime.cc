#include "drivers/stm32xx.h"
#include "time_convert.hh"

extern "C" uint32_t get_fattime() {
	return (uint32_t)ticks_to_fattime(HAL_GetTick());
}
