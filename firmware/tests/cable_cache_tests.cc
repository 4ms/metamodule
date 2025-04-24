#include "doctest.h"

#include "patch_play/cable_cache.hh"

TEST_CASE("cable_cache") {
	using namespace MetaModule;

	CableCache<2> cc;

	std::vector<InternalCable> cables;

	const uint16_t hub = 0;
	const uint16_t mod1 = 1;
	const uint16_t mod2 = 2;
	const uint16_t mod3 = 3;
	const uint16_t mod4 = 4;

	// core 0 -> 1
	cables.push_back({.out = {mod1, 1}, .ins = {{mod2, 20}}});
	// core 0 -> 0
	cables.push_back({.out = {mod1, 2}, .ins = {{mod3, 30}}});
	// core 0 -> 1, 0
	cables.push_back({.out = {mod1, 3}, .ins = {{mod2, 40}, {mod3, 50}}});

	// core 0 -> 0, 1
	cables.push_back({.out = {mod3, 4}, .ins = {{mod1, 60}, {mod2, 70}}});

	// core 1 -> 1, 1
	cables.push_back({.out = {mod2, 5}, .ins = {{mod4, 80}, {mod4, 90}}});

	CHECK(cables.size() == 5);

	std::array<std::vector<unsigned>, 2> core_assignments;
	// Core 0:
	core_assignments[0].push_back(hub);
	core_assignments[0].push_back(mod1);
	core_assignments[0].push_back(mod3);

	// Core 1
	core_assignments[1].push_back(mod2);
	core_assignments[1].push_back(mod4);

	cc.build(cables, core_assignments);

	CHECK(cc.outjacks[0].size() == 4);
	CHECK(cc.outjacks[0][0].is_tagged() == true);
	CHECK(cc.outjacks[0][1].is_tagged() == false);
	CHECK(cc.outjacks[0][2].is_tagged() == true);
	CHECK(cc.outjacks[0][3].is_tagged() == true);

	CHECK(cc.outjacks[1].size() == 1);
	CHECK(cc.outjacks[0][0].is_tagged() == false);
}
