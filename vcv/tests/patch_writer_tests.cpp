#include "doctest.h"
#include "patch_writer.hpp"
#include <iostream>

#include "ryml_serial.hpp"
//#include "ryml_all.hpp"

TEST_CASE("Basic hierarchal YAML Usage")
{
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	ryml::NodeRef level1 = root["Level1"];
	ryml::NodeRef level2 = root["Level2"];
	level1 |= ryml::MAP;
	level2 |= ryml::MAP;

	level1["subA"] = "item A within level 1";
	level1["subB"] = "item B within level 1";

	level2["subA"] = "item A within level 2";
	level2["subB"] = "item B within level 2";

	// clang-format off
	CHECK(ryml::emitrs<std::string>(tree) == R"(Level1:
  subA: item A within level 1
  subB: item B within level 1
Level2:
  subA: item A within level 2
  subB: item B within level 2
)");
	// clang-format on
}

TEST_CASE("Numbers as keys")
{
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	root["0"] = "SLUG1";
	root["1"] = "SLUG2";
	root["2"] = "SLUG3";

	CHECK(ryml::emitrs<std::string>(tree) ==
		  // clang-format off
R"(0: SLUG1
1: SLUG2
2: SLUG3
)");
	// clang-format on
}

TEST_CASE("Sequences")
{
	// Various methods found in the quickstart:
	// root.append_child() = "item1";
	//- item1
	// root["node"] |= ryml::SEQ;
	//- node: []
	// ryml::NodeRef node = root.append_child({ryml::KEYSEQ, "key"});
	// root.append_child() << ryml::key("key") << "val";
	// root |= ryml::SEQ; root.append_child() << "val";
	// root.append_child() << ryml::key("key") |= ryml::SEQ ;

	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	SUBCASE("Key is a string and value is a sequence of integers")
	{
		ryml::NodeRef int_cables = root.append_child({ryml::SEQ, "int_cables"});
		for (int i = 0; i < 3; i++) {
			int_cables.append_child() << i;
		}
		CHECK(ryml::emitrs<std::string>(tree) ==
			  // clang-format off
R"(int_cables:
  - 0
  - 1
  - 2
)");
		// clang-format on
	}

	SUBCASE("Key is a string and value is a sequence of maps")
	{
		SUBCASE("... Method 1")
		{
			ryml::NodeRef int_cables = root.append_child({ryml::KEYSEQ, "int_cables"});

			for (int i = 0; i < 3; i++) {
				ryml::NodeRef cable = int_cables.append_child({ryml::MAP});
				cable["out"] << i * 2 + 1;
				cable["in"] << i * 2 + 2;
			}
		}

		SUBCASE("... Method 2")
		{
			ryml::NodeRef int_cables = root["int_cables"];
			int_cables |= ryml::SEQ;

			for (int i = 0; i < 3; i++) {
				int_cables[i] |= ryml::MAP;
				int_cables[i]["out"] << i * 2 + 1;
				int_cables[i]["in"] << i * 2 + 2;
			}
		}

		SUBCASE("... Method 3")
		{
			root["int_cables"] |= ryml::SEQ;
			for (int i = 0; i < 3; i++) {
				root["int_cables"][i] |= ryml::MAP;
				root["int_cables"][i]["out"] << i * 2 + 1;
				root["int_cables"][i]["in"] << i * 2 + 2;
			}
		}

		CHECK(ryml::emitrs<std::string>(tree) ==
			  // clang-format off
R"(int_cables:
  - out: 1
    in: 2
  - out: 3
    in: 4
  - out: 5
    in: 6
)");
		// clang-format on
	}
}

void makeJack(ryml::NodeRef &n, Jack &jack)
{
	n |= ryml::MAP;
	n["module_id"] << jack.module_id;
	n["jack_id"] << jack.jack_id;
}

// This is defined in patch_writer.cpp
void write(ryml::NodeRef *n, Jack const &jack);

TEST_CASE("Can return a NodeRef")
{
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	Jack outjack{.module_id = 3, .jack_id = 44};

	SUBCASE("Method 1: Pass mutable reference to function")
	{
		ryml::NodeRef n = root["out"];
		makeJack(n, outjack);
	}

	SUBCASE("Method 2: Use write()")
	{
		root["out"] << outjack;
	}

	CHECK(ryml::emitrs<std::string>(tree) ==
		  // clang-format off
R"(out:
  module_id: 3
  jack_id: 44
)");
	// clang-format on
}

TEST_CASE("Can use const char[] for keys")
{
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	root["0"] = "000";
	root["1"] = "111";
	root.append_child() << ryml::key("2") << "222";

	const char numstrs[][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

	// Doesn't work:
	// root[numstrs[3]] << "333";

	root.append_child() << ryml::key(numstrs[4]) << "444";

	auto idx_s = std::to_string(5);
	ryml::csubstr idx(idx_s.c_str(), idx_s.length());
	root.append_child() << ryml::key(idx) << "555";

	// Doesn't work, presumably because idx6_s goes out of scope
	// for (int i = 6; i < 9; i++) {
	// 	auto idx6_s = std::to_string(i);
	// 	ryml::csubstr idx6(idx6_s.c_str(), idx6_s.length());
	// 	root[idx6] << "678";
	// }

	for (int i = 6; i < 9; i++) {
		auto idx_loop_s = std::to_string(i);
		ryml::csubstr idx_loop(idx_loop_s.c_str(), idx_loop_s.length());
		root.append_child() << ryml::key(idx_loop) << "678";
	}

	// Doesn't compile:
	// root.append_child() << ryml::key(ryml::csubstr{std::to_string(7).c_str(), 1}) << "777";

	CHECK(ryml::emitrs<std::string>(tree) ==
		  // clang-format off
R"(0: 000
1: 111
2: 222
4: 444
5: 555
6: 678
7: 678
8: 678
)");
	// clang-format on
}

TEST_CASE("Can parse patch header, field by field")
{
	// clang-format off
	char yml_buf[] =
R"(
PatchHeader:
  header_version: 1
  patch_name: test123
  num_modules: 4
  num_int_cables: 5
  num_mapped_ins: 6
  num_mapped_outs: 7
  num_static_knobs: 8
  num_mapped_knobs: 9
)";
	// clang-format on

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yml_buf));

	CHECK(tree.size() == 10); // Root + PatchHeader: + 8 children
	CHECK(tree[0].key() == "PatchHeader");
	CHECK(tree[0].num_children() == 8);
	CHECK(tree[0].child(0).key() == "header_version");
	CHECK(tree[0].child(1).key() == "patch_name");
	CHECK(tree[0].child(2).key() == "num_modules");
	CHECK(tree[0].child(3).key() == "num_int_cables");
	CHECK(tree[0].child(4).key() == "num_mapped_ins");
	CHECK(tree[0].child(5).key() == "num_mapped_outs");
	CHECK(tree[0].child(6).key() == "num_static_knobs");
	CHECK(tree[0].child(7).key() == "num_mapped_knobs");

	CHECK(tree[0].child(0).val() == "1");
	CHECK(tree[0].child(1).val() == "test123");
	CHECK(tree[0].child(2).val() == "4");
	CHECK(tree[0].child(3).val() == "5");
	CHECK(tree[0].child(4).val() == "6");
	CHECK(tree[0].child(5).val() == "7");
	CHECK(tree[0].child(6).val() == "8");
	CHECK(tree[0].child(7).val() == "9");

	PatchHeader ph;
	tree[0]["header_version"] >> ph.header_version;
	tree[0]["patch_name"] >> ph.patch_name;
	tree[0]["num_modules"] >> ph.num_modules;
	tree[0]["num_int_cables"] >> ph.num_int_cables;
	tree[0]["num_mapped_ins"] >> ph.num_mapped_ins;
	tree[0]["num_mapped_outs"] >> ph.num_mapped_outs;
	tree[0]["num_static_knobs"] >> ph.num_static_knobs;
	tree[0]["num_mapped_knobs"] >> ph.num_mapped_knobs;
	CHECK(ph.header_version == 1);
	CHECK(ph.patch_name.is_equal("test123"));
	CHECK(ph.num_modules == 4);
	CHECK(ph.num_int_cables == 5);
	CHECK(ph.num_mapped_ins == 6);
	CHECK(ph.num_mapped_outs == 7);
	CHECK(ph.num_static_knobs == 8);
	CHECK(ph.num_mapped_knobs == 9);
}

TEST_CASE("Can create a ryml::Tree from a PatchHeader using operator>>")
{
	ryml::Tree tree;
	PatchHeader ph_in{
		.header_version = 1,
		.patch_name = "test123",
		.num_modules = 4,
		.num_int_cables = 5,
		.num_mapped_ins = 6,
		.num_mapped_outs = 7,
		.num_static_knobs = 8,
		.num_mapped_knobs = 9,
	};
	tree.rootref() << ph_in;

	PatchHeader ph_out;
	tree.rootref() >> ph_out;
	CHECK(ph_out.header_version == ph_in.header_version);
	CHECK(ph_out.patch_name.is_equal(ph_in.patch_name));
	CHECK(ph_out.num_modules == ph_in.num_modules);
	CHECK(ph_out.num_int_cables == ph_in.num_int_cables);
	CHECK(ph_out.num_mapped_ins == ph_in.num_mapped_ins);
	CHECK(ph_out.num_mapped_outs == ph_in.num_mapped_outs);
	CHECK(ph_out.num_static_knobs == ph_in.num_static_knobs);
	CHECK(ph_out.num_mapped_knobs == ph_in.num_mapped_knobs);
}

TEST_CASE("Can parse patch header using operator<<")
{
	// clang-format off
	char yml_buf[] =
R"(
  header_version: 1
  patch_name: test123
  num_modules: 4
  num_int_cables: 5
  num_mapped_ins: 6
  num_mapped_outs: 7
  num_static_knobs: 8
  num_mapped_knobs: 9
)";
	// clang-format on

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yml_buf));

	PatchHeader ph_out;

	tree.rootref() >> ph_out;
	CHECK(ph_out.header_version == 1);
	CHECK(ph_out.patch_name.is_equal("test123"));
	CHECK(ph_out.num_modules == 4);
	CHECK(ph_out.num_int_cables == 5);
	CHECK(ph_out.num_mapped_ins == 6);
	CHECK(ph_out.num_mapped_outs == 7);
	CHECK(ph_out.num_static_knobs == 8);
	CHECK(ph_out.num_mapped_knobs == 9);
}

TEST_CASE("squash_ids() works")
{
	SUBCASE("y = id[x]  transforms to squashed[y] = x")
	{
		std::vector<int> ids = {1, 6, 25, 30, 9, 0, 2};
		auto sq = PatchFileWriter::squash_ids(ids);
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
		auto sq = PatchFileWriter::squash_ids(ids);
		CHECK(sq[30] == 0);
		CHECK(sq[11] == 1);
		CHECK(sq[6] == 2);
		CHECK(sq[0] == 3);
		CHECK(sq[1] == 4);
	}
}

TEST_CASE("ids are re-arranged properly")
{

	std::vector<ModuleID> modules;
	modules.push_back({11, "A"});
	modules.push_back({6, "B"});
	modules.push_back({30, "PANEL_8"});
	modules.push_back({0, "D"});
	modules.push_back({1, "E"});

	PatchFileWriter pw{modules};

	SUBCASE("modules_used starts with PANEL, but otherwise is in order")
	{
		CHECK(pw.get_data().module_slugs[0].cstr()[0] == 'P');
		CHECK(pw.get_data().module_slugs[1].cstr()[0] == 'A');
		CHECK(pw.get_data().module_slugs[2].cstr()[0] == 'B');
		CHECK(pw.get_data().module_slugs[3].cstr()[0] == 'D');
		CHECK(pw.get_data().module_slugs[4].cstr()[0] == 'E');
	}

	SUBCASE("Static Knob List is in order")
	{
		std::vector<ParamStatus> params;
		params.push_back({.value = 0.1f, .paramID = 1, .moduleID = 11});  // module A
		params.push_back({.value = 0.2f, .paramID = 2, .moduleID = 11});  // module A
		params.push_back({.value = 0.3f, .paramID = 3, .moduleID = 1});	  // module E
		params.push_back({.value = 0.001f, .paramID = 0, .moduleID = 0}); // module D
		params.push_back({.value = 6.f, .paramID = 6, .moduleID = 30});	  // module PANEL
		pw.setParamList(params);

		CHECK(pw.get_data().static_knobs[0].module_id == 1); // 11 = A -> 1
		CHECK(pw.get_data().static_knobs[1].module_id == 1); // 11 = A -> 1
		CHECK(pw.get_data().static_knobs[2].module_id == 4); // 1 = E -> 4
		CHECK(pw.get_data().static_knobs[3].module_id == 3); // 0 = D -> 3
		CHECK(pw.get_data().static_knobs[4].module_id == 0); // 30 = PANEL -> 0
	}
}
