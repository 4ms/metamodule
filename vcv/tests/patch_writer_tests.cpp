#include "doctest.h"
#include "patch_writer.hh"
#include <iostream>

TEST_CASE("squash_ids() works")
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
		CHECK(p.modules_used[0].name[0] == 'P');
		CHECK(p.modules_used[1].name[0] == 'A');
		CHECK(p.modules_used[2].name[0] == 'B');
		CHECK(p.modules_used[3].name[0] == 'D');
		CHECK(p.modules_used[4].name[0] == 'E');
	}

	SUBCASE("Static Knob List is in order")
	{
		std::vector<ParamStatus> params;
		params.push_back({.moduleID = 11, .paramID = 1, .value = 0.1f});  // module A
		params.push_back({.moduleID = 11, .paramID = 2, .value = 0.2f});  // module A
		params.push_back({.moduleID = 1, .paramID = 3, .value = 0.3f});	  // module E
		params.push_back({.moduleID = 0, .paramID = 0, .value = 0.001f}); // module D
		params.push_back({.moduleID = 30, .paramID = 6, .value = 6.f});	  // module PANEL
		pw.copyParamList(params);

		pw.createPatch();
		CHECK(p.static_knobs[0].module_id == 1); // 11 = A -> 1
		CHECK(p.static_knobs[1].module_id == 1); // 11 = A -> 1
		CHECK(p.static_knobs[2].module_id == 4); // 1 = E -> 4
		CHECK(p.static_knobs[3].module_id == 3); // 0 = D -> 3
		CHECK(p.static_knobs[4].module_id == 0); // 30 = PANEL -> 0
	}
}

