#include "VCV_adaptor/random.hpp"
#include "drivers/stm32xx.h"

namespace rack::random
{

static Xoroshiro128Plus rng;

void init() {
	// Don't reset state if already seeded
	if (rng.isSeeded())
		return;

	// FIXME: For Cortex-A7: read RNG four times => two 64-bit numbers
	uint64_t time = PL1_GetCurrentPhysicalValue();
	uint64_t nsec = HAL_GetTick();

	rng.seed(time, nsec);

	// Shift state a few times due to low seed entropy
	for (int i = 0; i < 4; i++) {
		rng();
	}
}

Xoroshiro128Plus &local() {
	return rng;
}

} // namespace rack::random
