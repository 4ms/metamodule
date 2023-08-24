#include "VCV_adaptor/random.hpp"
#include "drivers/rcc.hh"
#include "drivers/stm32xx.h"

namespace rack::random
{

static Xoroshiro128Plus rng;

void init() {
	// Don't reset state if already seeded
	if (rng.isSeeded())
		return;

	mdrivlib::RCC_Enable::RNG1_::set();

	RNG_HandleTypeDef hrng{
		.Instance = RNG1,
		.Init = {.ClockErrorDetection = RNG_CED_DISABLE},
		.Lock = HAL_UNLOCKED,
		.State = HAL_RNG_STATE_RESET,
		.ErrorCode = HAL_RNG_ERROR_NONE,
	};
	HAL_RNG_Init(&hrng);

	uint32_t nums[4] = {0, 0, 0, 0};

	for (auto &num : nums) {
		if (HAL_RNG_GenerateRandomNumber(&hrng, &num) != HAL_OK) {
			// pr_err("RNG failed to generate a random number\n");
			return;
		}
		// printf_("Random: %ld\n", num);
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
