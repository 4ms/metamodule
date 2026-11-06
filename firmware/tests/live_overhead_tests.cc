#include "doctest.h"
#include "patch_play/live_overhead.hh"
#include <vector>

using namespace MetaModule;

namespace
{

LiveLoadMeter::Loads two_core_loads() {
	LiveLoadMeter::Loads live{};
	live.mappings = 12; // tenths of a percent
	live.midi = 3;
	live.overhead = 20;
	live.cables = 10;
	live.core2_cables = 5;
	live.sync = 50;
	live.sync2 = 10;
	live.modules[1] = 200; // core 0
	live.modules[2] = 150; // core 1
	live.modules[3] = 100; // core 1
	live.valid = true;
	return live;
}

} // namespace

TEST_CASE("overhead is computed like the Load Balance panel") {
	auto live = two_core_loads();
	std::vector<uint16_t> cores{0, 0, 1, 1}; // module 0 is the Hub

	auto oh = live_overhead(live, cores);

	// core 0: cables 10 + module 200 = 210; core 1: cables 5 + 150 + 100 = 255 (busiest)
	CHECK(oh.cores[0] == 210'000);
	CHECK(oh.cores[1] == 255'000);
	CHECK(oh.core_tenths(0) == 210);
	CHECK(oh.core_tenths(1) == 255);
	CHECK(oh.max_core == 255'000);
	// core 0 runs 210 + sync 60 = 270, which is 15 beyond the busiest core
	CHECK(oh.sync == 15'000);
	CHECK(oh.mappings == 12'000);
	CHECK(oh.midi == 3'000);
	CHECK(oh.other == 20'000);
	CHECK(oh.total() == 50'000);
	CHECK(oh.total_tenths() == 50);
}

TEST_CASE("no sync overhead when core 0 isn't waiting beyond the busiest core") {
	auto live = two_core_loads();
	live.sync = 20;
	live.sync2 = 0;
	std::vector<uint16_t> cores{0, 0, 1, 1};

	// core 0: 210 + 20 = 230 < 255
	CHECK(live_overhead(live, cores).sync == 0);
}

TEST_CASE("patch without core assignments has no sync overhead") {
	auto live = two_core_loads();
	std::vector<uint16_t> cores{};

	auto oh = live_overhead(live, cores);
	CHECK(oh.sync == 0);
	CHECK(oh.total_tenths() == 35);
}

TEST_CASE("overhead tenths are rounded") {
	LiveLoadMeter::Loads live{};
	std::vector<uint16_t> cores{};
	live.overhead = 7;

	auto oh = live_overhead(live, cores);
	oh.other = 7'600; // 7.6 tenths
	CHECK(oh.total_tenths() == 8);
}
