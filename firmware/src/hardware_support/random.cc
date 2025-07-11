#include "drivers/rcc.hh"
#include <cstdint>
#include <cstdlib>

namespace MetaModule::System
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

__attribute__((visibility("hidden"))) bool hardware_random_init() {
	mdrivlib::RCC_Enable::RNG1_::set();

	RNG1->CR = RNG1->CR | RNG_CED_DISABLE;
	RNG1->CR |= RNG_CR_RNGEN;

	return true;
}

// globally init the random peripheral once
static auto s_hardware_random_init = hardware_random_init();

} // namespace MetaModule::System
