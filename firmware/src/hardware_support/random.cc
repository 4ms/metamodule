#include "drivers/stm32xx.h"
#include <cstdint>
#include <cstdlib>

namespace MetaModule
{

bool hardware_random_ready() {
	return (RNG1->SR & RNG_FLAG_DRDY) == RNG_FLAG_DRDY;
}

uint32_t hardware_random() {
	return RNG1->DR;
}

uint32_t random() {
	return std::rand();
}

} // namespace MetaModule
