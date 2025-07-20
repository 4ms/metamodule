#pragma once
#include <cstdint>

namespace MetaModule::System
{
uint32_t get_ticks();
void delay_ms(uint32_t);
} // namespace MetaModule::System

inline uint64_t get_time() {
	return MetaModule::System::get_ticks();
}

inline void delay_ms(uint32_t ms) {
	MetaModule::System::delay_ms(ms);
}
