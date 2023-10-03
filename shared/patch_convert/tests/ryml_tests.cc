#include "doctest.h"
#include <iostream>

#include "ryml_serial.hh"

TEST_CASE("Basic hierarchal YAML Usage") {
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
	CHECK(ryml::emitrs_yaml<std::string>(tree) == R"(Level1:
  subA: item A within level 1
  subB: item B within level 1
Level2:
  subA: item A within level 2
  subB: item B within level 2
)");
	// clang-format on
}

TEST_CASE("Numbers as keys") {
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	root["0"] = "SLUG1";
	root["1"] = "SLUG2";
	root["2"] = "SLUG3";

	CHECK(ryml::emitrs_yaml<std::string>(tree) ==
		  // clang-format off
R"(0: SLUG1
1: SLUG2
2: SLUG3
)");
	// clang-format on
}

TEST_CASE("Sequences") {
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

	SUBCASE("Key is a string and value is a sequence of integers") {
		ryml::NodeRef int_cables = root.append_child({ryml::SEQ, "int_cables"});
		for (int i = 0; i < 3; i++) {
			int_cables.append_child() << i;
		}
		CHECK(ryml::emitrs_yaml<std::string>(tree) ==
			  // clang-format off
R"(int_cables:
  - 0
  - 1
  - 2
)");
		// clang-format on
	}

	SUBCASE("Key is a string and value is a sequence of maps") {
		SUBCASE("... Method 1") {
			ryml::NodeRef int_cables = root.append_child({ryml::KEYSEQ, "int_cables"});

			for (int i = 0; i < 3; i++) {
				ryml::NodeRef cable = int_cables.append_child({ryml::MAP});
				cable["out"] << i * 2 + 1;
				cable["in"] << i * 2 + 2;
			}
		}

		SUBCASE("... Method 2") {
			ryml::NodeRef int_cables = root["int_cables"];
			int_cables |= ryml::SEQ;

			for (int i = 0; i < 3; i++) {
				int_cables[i] |= ryml::MAP;
				int_cables[i]["out"] << i * 2 + 1;
				int_cables[i]["in"] << i * 2 + 2;
			}
		}

		SUBCASE("... Method 3") {
			root["int_cables"] |= ryml::SEQ;
			for (int i = 0; i < 3; i++) {
				root["int_cables"][i] |= ryml::MAP;
				root["int_cables"][i]["out"] << i * 2 + 1;
				root["int_cables"][i]["in"] << i * 2 + 2;
			}
		}

		CHECK(ryml::emitrs_yaml<std::string>(tree) ==
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

void makeJack(ryml::NodeRef &n, Jack &jack) {
	n |= ryml::MAP;
	n["module_id"] << jack.module_id;
	n["jack_id"] << jack.jack_id;
}

// This is defined in patch_writer.cpp
void write(ryml::NodeRef *n, Jack const &jack);

TEST_CASE("Can return a NodeRef") {
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	Jack outjack{.module_id = 3, .jack_id = 44};

	SUBCASE("Method 1: Pass mutable reference to function") {
		ryml::NodeRef n = root["out"];
		makeJack(n, outjack);
	}

	SUBCASE("Method 2: Use write()") {
		root["out"] << outjack;
	}

	CHECK(ryml::emitrs_yaml<std::string>(tree) ==
		  // clang-format off
R"(out:
  module_id: 3
  jack_id: 44
)");
	// clang-format on
}

TEST_CASE("Can use const char[] for keys") {
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

	CHECK(ryml::emitrs_yaml<std::string>(tree) ==
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

struct SomeStruct {
	int header_version;
	StaticString<31> patch_name;
	int num_modules;
	int num_int_cables;
	int num_mapped_ins;
	int num_mapped_outs;
	int num_static_knobs;
	int num_mapped_knobs;
};

TEST_CASE("Can parse a struct, field by field") {
	// clang-format off
	char yml_buf[] =
R"(SomeStruct:
  header_version: 1
  patch_name: "test123"
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
	CHECK(tree[0].key() == "SomeStruct");
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

	SomeStruct ph;
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

TEST_CASE("Multiple root-level siblings") {
	char yml_buf[] = R"(
Sibling0:
  data1: 1
'Sibling1':
  'data3': 'ABCD'
  'data4': 9
  'data5': UNQUOTED 
  data2: "test123"
'Sibling2':
)";

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yml_buf));

	CHECK(tree.size() == 9); // Root + 8 elements (essentially 1 + Number of Lines)

	// Different ways of seeing how many root-level siblings
	CHECK(tree.num_children(0) == 3); //number of children of node 0 (root node)
	CHECK(tree.num_siblings(1) == 3); //number of siblings of node 1 (Sibling0)

	auto root = tree.rootref();
	CHECK(root.num_children() == 3);

	CHECK(root.has_child("Sibling0"));
	CHECK(root.has_child("Sibling1"));
	CHECK(root.has_child("Sibling2"));
	CHECK(!root.has_child("Sibling3"));

	ryml::ConstNodeRef sib0 = root["Sibling0"];
	ryml::ConstNodeRef sib1 = root["Sibling1"];
	ryml::ConstNodeRef sib2 = root["Sibling2"];

	CHECK(sib0.key() == "Sibling0");
	CHECK(sib0.num_children() == 1);
	CHECK(sib0.child(0).key() == "data1");
	CHECK(sib0.child(0).val() == "1");

	CHECK(sib1.key() == "Sibling1");
	CHECK(sib1.num_children() == 4);
	CHECK(sib1.child(0).key() == "data3");
	CHECK(sib1.child(0).val() == "ABCD");
	CHECK(sib1.child(1).key() == "data4");
	CHECK(sib1.child(1).val() == "9");
	CHECK(sib1.child(2).key() == "data5");
	CHECK(sib1.child(2).val() == "UNQUOTED");
	CHECK(sib1.child(3).key() == "data2");
	CHECK(sib1.child(3).val() == "test123");

	CHECK(sib2.key() == "Sibling2");
	CHECK(sib2.num_children() == 0);
}
