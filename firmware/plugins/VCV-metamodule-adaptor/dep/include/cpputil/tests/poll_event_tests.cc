#include "../util/poll_event.hh"
#include "doctest.h"
#include <concepts>
#include <cstddef>
#include <cstdint>

template<std::unsigned_integral TimeT>
void test_overflow(TimeT starting_time, unsigned num_reps = 13) {
	constexpr size_t period = 4;

	// For simplicity we require that the simulated "clock" has been running for a while
	REQUIRE(starting_time > period);

	bool flag = false;
	auto action = [&flag] { flag = true; };

	PollEvent<TimeT> p{period};
	TimeT now = starting_time;

	for (unsigned i = 0; i < num_reps; i++) {
		p.poll(now, action);

		// The action should be called every `period` polls
		CHECK(flag == ((i % period) == 0));

		// simulate passage of time
		now++;

		// reset state
		flag = false;
	}
}

TEST_CASE("Unsigned uint8_t overflow of system time") {

	// Test at various starting times
	// so action() happens at different times w.r.t. overflow

	test_overflow<uint8_t>(UINT8_MAX - 5);
	test_overflow<uint8_t>(UINT8_MAX - 4);
	test_overflow<uint8_t>(UINT8_MAX - 3);
	test_overflow<uint8_t>(UINT8_MAX - 2);
	test_overflow<uint8_t>(UINT8_MAX - 1);
	test_overflow<uint8_t>(UINT8_MAX - 0);

	test_overflow<uint16_t>(UINT16_MAX - 5);
	test_overflow<uint16_t>(UINT16_MAX - 4);
	test_overflow<uint16_t>(UINT16_MAX - 3);
	test_overflow<uint16_t>(UINT16_MAX - 2);
	test_overflow<uint16_t>(UINT16_MAX - 1);
	test_overflow<uint16_t>(UINT16_MAX - 0);

	test_overflow<uint32_t>(UINT32_MAX - 5);
	test_overflow<uint32_t>(UINT32_MAX - 4);
	test_overflow<uint32_t>(UINT32_MAX - 3);
	test_overflow<uint32_t>(UINT32_MAX - 2);
	test_overflow<uint32_t>(UINT32_MAX - 1);
	test_overflow<uint32_t>(UINT32_MAX - 0);

	test_overflow<uint64_t>(UINT64_MAX - 5);
	test_overflow<uint64_t>(UINT64_MAX - 4);
	test_overflow<uint64_t>(UINT64_MAX - 3);
	test_overflow<uint64_t>(UINT64_MAX - 2);
	test_overflow<uint64_t>(UINT64_MAX - 1);
	test_overflow<uint64_t>(UINT64_MAX - 0);
}
