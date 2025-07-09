#include "random.hpp"
#include "system/random.hh"

namespace rack::random
{

static Xoroshiro128Plus rng;

void init() {
	// Don't reset state if already seeded
	if (rng.isSeeded())
		return;

	uint32_t nums[4] = {0, 0, 0, 0};

	for (auto &num : nums) {
		while (!MetaModule::hardware_random_ready()) {
		}
		num = MetaModule::hardware_random();
	}

	uint64_t seed1 = ((uint64_t)(nums[0])) << 32;
	seed1 |= nums[1];
	uint64_t seed2 = ((uint64_t)(nums[2])) << 32;
	seed2 |= nums[3];

	rng.seed(seed1, seed2);
}

Xoroshiro128Plus &local() {
	return rng;
}

} // namespace rack::random
