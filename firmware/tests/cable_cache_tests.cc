#include "doctest.h"

#include "patch_play/cable_cache.hh"

TEST_CASE("cable_cache") {
	using namespace MetaModule;

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
	// core 1 -> 0
	cables.push_back({.out = {mod2, 6}, .ins = {{mod1, 100}}});

	std::array<std::vector<unsigned>, 2> core_assignments;

	// Core 0:
	core_assignments[0].push_back(hub);
	core_assignments[0].push_back(mod1);
	core_assignments[0].push_back(mod3);

	// Core 1
	core_assignments[1].push_back(mod2);
	core_assignments[1].push_back(mod4);

	CableCache<2> cc;
	cc.build(cables, core_assignments);

	// CHECK(cc._cables[0].size() == 6);
	// CHECK(cc._cables[0][0].out.is_tagged() == true);
	// CHECK(cc._cables[0][1].out.is_tagged() == false);
	// CHECK(cc._cables[0][2].out.is_tagged() == true);
	// CHECK(cc._cables[0][3].out.is_tagged() == true);

	// CHECK(cc._cables[1].size() == 2);
	// CHECK(cc.outjacks[1][0].is_tagged() == false);
	// CHECK(cc.outjacks[1][1].is_tagged() == true);

	// CHECK(cc.cables[0][0].out.module_id_only() == mod1);
	// CHECK(cc.cables[0][0].out.jack_id == 1);
	// CHECK(cc.cables[0][mod2][0].in.jack_id == 20);
	// CHECK((cc.ins[mod2][0].out_core_id == 0));
	// CHECK((cc.ins[mod2][0].out_cache_idx == 0)); //mod1 outjack 1 is outvals[0][0]

	// CHECK(cc.outjacks[0][1].module_id_only() == mod1);
	// CHECK(cc.outjacks[0][1].jack_id == 2);
	// CHECK(cc.ins[mod3][0].jack_id == 30);
	// CHECK(cc.ins[mod3][0].out_core_id == 0);
	// CHECK(cc.ins[mod3][0].out_cache_idx == 1); //mod1 outjack 2 is outvals[0][1]

	// CHECK(cc.outjacks[0][2].module_id_only() == mod1);
	// CHECK(cc.outjacks[0][2].jack_id == 3);
	// CHECK(cc.ins[mod2][1].jack_id == 40);
	// CHECK(cc.ins[mod2][1].out_core_id == 0);
	// CHECK(cc.ins[mod2][1].out_cache_idx == 2); //mod1 outjack 3 is outvals[0][2]
	// CHECK(cc.ins[mod3][1].jack_id == 50);
	// CHECK(cc.ins[mod3][1].out_core_id == 0);
	// CHECK(cc.ins[mod3][1].out_cache_idx == 2); //outvals[0][2]

	// CHECK(cc.outjacks[0][3].module_id_only() == mod3);
	// CHECK(cc.outjacks[0][3].jack_id == 4);
	// CHECK(cc.ins[mod1][0].jack_id == 60);
	// CHECK(cc.ins[mod1][0].out_core_id == 0);
	// CHECK(cc.ins[mod1][0].out_cache_idx == 3); //mod3 outjack 4 is outvals[0][3]

	// CHECK(cc.outjacks[1][0].module_id_only() == mod2);
	// CHECK(cc.outjacks[1][0].jack_id == 5);
	// CHECK(cc.ins[mod4][0].jack_id == 80);
	// CHECK(cc.ins[mod4][0].out_core_id == 1);
	// CHECK(cc.ins[mod4][0].out_cache_idx == 0); //mod2 outjack 5 is outvals[1][0]
	// CHECK(cc.ins[mod4][1].jack_id == 90);
	// CHECK(cc.ins[mod4][1].out_core_id == 1);
	// CHECK(cc.ins[mod4][1].out_cache_idx == 0); //outvals[1][0]

	// CHECK(cc.outjacks[1][1].module_id_only() == mod2);
	// CHECK(cc.outjacks[1][1].jack_id == 6);
	// CHECK(cc.ins[mod1][1].jack_id == 100);
	// CHECK(cc.ins[mod1][1].out_core_id == 1);
	// CHECK(cc.ins[mod1][1].out_cache_idx == 1); //mod2 outjack 6 is outvals[1][1]

	// CHECK(cc.ins[mod1].size() == 2);
	// CHECK(cc.ins[mod2].size() == 3);
	// CHECK(cc.ins[mod3].size() == 2);
	// CHECK(cc.ins[mod4].size() == 2);

	// printf("-----------------------------\n");
}
