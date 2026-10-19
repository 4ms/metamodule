#include <cstdint>
#include <cstdlib>

// MP2 version of src/hardware_support/random.cc
// FIXME: use the MP25's RNG peripheral. Until then the "hardware" random numbers come from rand().

namespace MetaModule::System
{

bool hardware_random_ready() {
	return true;
}

uint32_t hardware_random() {
	return std::rand();
}

uint32_t random() {
	return std::rand();
}

} // namespace MetaModule::System
