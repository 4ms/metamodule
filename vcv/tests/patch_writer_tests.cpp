#include "doctest.h"
#include "patch_writer.hh"
#include <iostream>

TEST_CASE("squash_ids() works")
{
	SUBCASE("y = id[x]  transfomrs to squashed[y] = x")
	{
		std::vector<int> ids = {1, 6, 25, 30, 9, 0, 2};
		auto sq = PatchWriter::squash_ids(ids);
		CHECK(sq[1] == 0);
		CHECK(sq[6] == 1);
		CHECK(sq[25] == 2);
		CHECK(sq[30] == 3);
		CHECK(sq[9] == 4);
		CHECK(sq[0] == 5);
		CHECK(sq[2] == 6);
	}

	SUBCASE("y = id[x]  transforms to squashed[y] = x (just another test of the same thing)")
	{
		std::vector<int> ids = {30, 11, 6, 0, 1};
		auto sq = PatchWriter::squash_ids(ids);
		CHECK(sq[30] == 0);
		CHECK(sq[11] == 1);
		CHECK(sq[6] == 2);
		CHECK(sq[0] == 3);
		CHECK(sq[1] == 4);
	}
}

TEST_CASE("ids are re-arranged properly")
{
	Patch p;
	PatchWriter pw{p};

	std::vector<ModuleID> modules;
	modules.push_back({11, "A"});
	modules.push_back({6, "B"});
	modules.push_back({30, "PANEL_8"});
	modules.push_back({0, "D"});
	modules.push_back({1, "E"});

	pw.copyModuleList(modules);

	SUBCASE("modules_used starts with PANEL, but otherwise is in order")
	{
		pw.createPatch();
		CHECK(p.modules_used[0].cstr()[0] == 'P');
		CHECK(p.modules_used[1].cstr()[0] == 'A');
		CHECK(p.modules_used[2].cstr()[0] == 'B');
		CHECK(p.modules_used[3].cstr()[0] == 'D');
		CHECK(p.modules_used[4].cstr()[0] == 'E');
	}

	SUBCASE("Static Knob List is in order")
	{
		std::vector<ParamStatus> params;
		params.push_back({.value = 0.1f, .paramID = 1, .moduleID = 11});  // module A
		params.push_back({.value = 0.2f, .paramID = 2, .moduleID = 11});  // module A
		params.push_back({.value = 0.3f, .paramID = 3, .moduleID = 1});	  // module E
		params.push_back({.value = 0.001f, .paramID = 0, .moduleID = 0}); // module D
		params.push_back({.value = 6.f, .paramID = 6, .moduleID = 30});	  // module PANEL
		pw.copyParamList(params);

		pw.createPatch();
		CHECK(p.static_knobs[0].module_id == 1); // 11 = A -> 1
		CHECK(p.static_knobs[1].module_id == 1); // 11 = A -> 1
		CHECK(p.static_knobs[2].module_id == 4); // 1 = E -> 4
		CHECK(p.static_knobs[3].module_id == 3); // 0 = D -> 3
		CHECK(p.static_knobs[4].module_id == 0); // 30 = PANEL -> 0
	}
}

