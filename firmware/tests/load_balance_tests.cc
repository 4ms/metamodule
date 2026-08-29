#include "doctest.h"
#include "patch_play/balance_modules.hh"
#include <array>
#include <numeric>

using Balancer = MetaModule::Balancer<2, 64>;

static unsigned core_sum(Balancer::Arrangement const &arr, std::span<const unsigned> times, unsigned core) {
	unsigned sum = 0;
	for (auto i = 0u; i < times.size(); i++) {
		if (arr.core_of[i + 1] == core)
			sum += times[i];
	}
	return sum;
}

TEST_CASE("Plain balance splits the load evenly") {
	// times are indexed by (module id - 1).
	// They need to be much larger than the bias given to the second core,
	// which is what a real measurement looks like.
	auto times = std::array{10000u, 9000u, 8000u, 7000u, 6000u, 5000u};

	auto arr = Balancer::make_arrangement(times, 0);

	auto total = std::accumulate(times.begin(), times.end(), 0u);
	auto core0 = core_sum(arr, times, 0);
	auto core1 = core_sum(arr, times, 1);

	CHECK(core0 + core1 == total);
	// Perfectly balanced except for the bias given to the second core
	CHECK(core0 >= core1);
	CHECK(core0 - core1 <= Balancer::SecondCoreBias);
}

TEST_CASE("Plain balance is deterministic") {
	auto times = std::array{11000u, 3000u, 27000u, 5000u, 19000u, 2000u, 8000u};

	auto a = Balancer::make_arrangement(times, 0);
	auto b = Balancer::make_arrangement(times, 0);

	CHECK(a.core_of == b.core_of);
	CHECK(a.imbalance == b.imbalance);
}

TEST_CASE("A seed gives an alternate arrangement of similar quality") {
	auto times = std::array{11000u, 3000u, 27000u, 5000u, 19000u, 2000u, 8000u, 14000u, 6000u, 21000u};

	auto plain = Balancer::make_arrangement(times, 0);
	auto total = std::accumulate(times.begin(), times.end(), 0u);

	bool found_different = false;
	for (auto seed = 1u; seed <= 16u; seed++) {
		auto alt = Balancer::make_arrangement(times, seed * 2654435761u);
		CHECK(core_sum(alt, times, 0) + core_sum(alt, times, 1) == total);
		if (alt.core_of != plain.core_of && alt.imbalance <= plain.imbalance + total / 50)
			found_different = true;
	}
	CHECK(found_different);
}

TEST_CASE("Re-calculating prefers a different arrangement") {
	Balancer balancer;

	auto times = std::array{11000u, 3000u, 27000u, 5000u, 19000u, 2000u, 8000u, 14000u, 6000u, 21000u};

	auto first = balancer.balance_loads(times);

	std::vector<uint16_t> prev(times.size() + 1, 0);
	for (auto i = 1u; i <= times.size(); i++)
		prev[i] = first.core_of[i];

	auto second = balancer.balance_loads(times, prev);

	bool differs = false;
	for (auto i = 1u; i <= times.size(); i++) {
		if (second.core_of[i] != prev[i])
			differs = true;
	}
	CHECK(differs);

	// And the parts were updated to match
	unsigned num_assigned = 0;
	for (auto core = 0u; core < 2; core++) {
		for (auto module_id : balancer.cores.parts[core]) {
			CHECK(second.core_of[module_id] == core);
			num_assigned++;
		}
	}
	CHECK(num_assigned == times.size());
}

TEST_CASE("Re-calculating never gives up much balance to be different") {
	Balancer balancer;

	auto times = std::array{11000u, 3000u, 27000u, 5000u, 19000u, 2000u, 8000u, 14000u, 6000u, 21000u};
	auto total = std::accumulate(times.begin(), times.end(), 0u);

	auto first = balancer.balance_loads(times);

	std::vector<uint16_t> prev(times.size() + 1, 0);
	for (auto i = 1u; i <= times.size(); i++)
		prev[i] = first.core_of[i];

	// However many times it is re-rolled, the result stays close to the best split
	for (auto i = 0u; i < 10u; i++) {
		auto next = balancer.balance_loads(times, prev);
		CHECK(next.imbalance <= first.imbalance + total / 50);

		for (auto id = 1u; id <= times.size(); id++)
			prev[id] = next.core_of[id];
	}
}

TEST_CASE("A stored balance is applied without measuring") {
	Balancer balancer;

	std::vector<uint16_t> cores{0, 1, 0, 1, 1};
	balancer.apply_stored_balance(cores);

	CHECK(balancer.cores.parts[0].size() == 1);
	CHECK(balancer.cores.parts[0][0] == 2);

	CHECK(balancer.cores.parts[1].size() == 3);
	CHECK(balancer.cores.parts[1][0] == 1);
	CHECK(balancer.cores.parts[1][1] == 3);
	CHECK(balancer.cores.parts[1][2] == 4);
}

TEST_CASE("Ticks convert to a percentage of one core") {
	// 24MHz counter, 48kHz sample rate => 500 ticks available per sample.
	// A module using 50 ticks per sample uses 10% of one core.
	auto ticks = 50u * Balancer::NumIterations;
	CHECK(Balancer::ticks_to_ppm(ticks, 48000.f) == 100'000);

	CHECK(Balancer::ticks_to_ppm(0, 48000.f) == 0);
	CHECK(Balancer::ticks_to_ppm(1000, 0.f) == 0);
}
