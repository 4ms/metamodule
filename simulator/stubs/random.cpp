#include "random.hpp"
#include <time.h>

namespace rack::random
{

static Xoroshiro128Plus rng;

void init() {
	// Don't reset state if already seeded
	if (rng.isSeeded())
		return;

	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	rng.seed(ts.tv_sec, ts.tv_nsec);

	// Shift state a few times due to low seed entropy
	for (int i = 0; i < 4; i++) {
		rng();
	}
}

Xoroshiro128Plus &local() {
	return rng;
}

} // namespace rack::random
