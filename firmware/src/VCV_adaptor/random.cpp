#include "VCV_adaptor/random.hpp"
#include "stm32mp1xx_hal.h"

namespace rack::random
{

static Xoroshiro128Plus rng;

void init() {
	// Don't reset state if already seeded
	if (rng.isSeeded())
		return;

	// Get epoch time for seed
	double time = HAL_GetTick();
	uint64_t sec = time;
	uint64_t nsec = std::fmod(time, 1.0) * 1e9;
	rng.seed(sec, nsec);

	// Shift state a few times due to low seed entropy
	for (int i = 0; i < 4; i++) {
		rng();
	}
}

Xoroshiro128Plus &local() {
	return rng;
}

} // namespace rack::random
