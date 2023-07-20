#include "patchlist_ryml_tests.hh"
#include "patch/patch_data.hh"
#include "patch_convert/yaml_to_patch.hh"
#include "ryml/ryml_serial.hh"

namespace
{
#define CHECK(x)                                                                                                       \
	if (!(x))                                                                                                          \
		return false;

bool TEST_CASE_Basic_hierarchal_YAML_Usage() {
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

	return true;
}

bool TEST_CASE_Numbers_as_keys() {
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
	return true;
}

bool TEST_CASE_Sequences() {
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

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
	return true;
}

bool TEST_CASE_Sequences2() {
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	// SUBCASE("Key is a string and value is a sequence of maps") {
	// 	SUBCASE("... Method 1") {
	// 		ryml::NodeRef int_cables = root.append_child({ryml::KEYSEQ, "int_cables"});

	// 		for (int i = 0; i < 3; i++) {
	// 			ryml::NodeRef cable = int_cables.append_child({ryml::MAP});
	// 			cable["out"] << i * 2 + 1;
	// 			cable["in"] << i * 2 + 2;
	// 		}
	// 	}

	// 	SUBCASE("... Method 2") {
	// 		ryml::NodeRef int_cables = root["int_cables"];
	// 		int_cables |= ryml::SEQ;

	// 		for (int i = 0; i < 3; i++) {
	// 			int_cables[i] |= ryml::MAP;
	// 			int_cables[i]["out"] << i * 2 + 1;
	// 			int_cables[i]["in"] << i * 2 + 2;
	// 		}
	// 	}

	// 	SUBCASE("... Method 3") {
	root["int_cables"] |= ryml::SEQ;
	for (int i = 0; i < 3; i++) {
		root["int_cables"][i] |= ryml::MAP;
		root["int_cables"][i]["out"] << i * 2 + 1;
		root["int_cables"][i]["in"] << i * 2 + 2;
	}
	// }

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
	// }
	return true;
}

void makeJack(ryml::NodeRef &n, Jack &jack) {
	n |= ryml::MAP;
	n["module_id"] << jack.module_id;
	n["jack_id"] << jack.jack_id;
}

// This is defined in patch_writer.cpp
void write(ryml::NodeRef *n, Jack const &jack);

bool TEST_CASE_Can_return_a_NodeRef() {
	ryml::Tree tree;
	ryml::NodeRef root = tree.rootref();
	root |= ryml::MAP;

	Jack outjack{.module_id = 3, .jack_id = 44};

	// SUBCASE("Method 1: Pass mutable reference to function") {
	ryml::NodeRef n = root["out1"];
	makeJack(n, outjack);
	// }

	// SUBCASE("Method 2: Use write()") {
	root["out2"] << outjack;
	// }

	CHECK(ryml::emitrs<std::string>(tree) ==
		  // clang-format off
R"(out1:
  module_id: 3
  jack_id: 44
out2:
  module_id: 3
  jack_id: 44
)");
	// clang-format on
	return true;
}

bool TEST_CASE_Can_use_const_char_for_keys() {
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
	return true;
}

bool TEST_CASE_Can_parse_a_struct_field_by_field() {
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

	// PatchHeader ph;
	// tree[0]["header_version"] >> ph.header_version;
	// tree[0]["patch_name"] >> ph.patch_name;
	// tree[0]["num_modules"] >> ph.num_modules;
	// tree[0]["num_int_cables"] >> ph.num_int_cables;
	// tree[0]["num_mapped_ins"] >> ph.num_mapped_ins;
	// tree[0]["num_mapped_outs"] >> ph.num_mapped_outs;
	// tree[0]["num_static_knobs"] >> ph.num_static_knobs;
	// tree[0]["num_mapped_knobs"] >> ph.num_mapped_knobs;
	// CHECK(ph.header_version == 1);
	// CHECK(ph.patch_name.is_equal("test123"));
	// CHECK(ph.num_modules == 4);
	// CHECK(ph.num_int_cables == 5);
	// CHECK(ph.num_mapped_ins == 6);
	// CHECK(ph.num_mapped_outs == 7);
	// CHECK(ph.num_static_knobs == 8);
	// CHECK(ph.num_mapped_knobs == 9);

	return true;
}

struct _TestPatchHeader {
	uint32_t header_version;

	ModuleTypeSlug patch_name;

	uint16_t num_modules;
	uint16_t num_int_cables;

	uint16_t num_mapped_ins;
	uint16_t num_mapped_outs;

	uint16_t num_static_knobs;
	uint16_t num_mapped_knobs;
};

void write(ryml::NodeRef *n, _TestPatchHeader const &ph) {
	*n |= ryml::MAP;
	n->append_child() << ryml::key("header_version") << std::to_string(ph.header_version);
	n->append_child() << ryml::key("patch_name") << ph.patch_name.c_str();
	n->append_child() << ryml::key("num_modules") << std::to_string(ph.num_modules);
	n->append_child() << ryml::key("num_int_cables") << std::to_string(ph.num_int_cables);
	n->append_child() << ryml::key("num_mapped_ins") << std::to_string(ph.num_mapped_ins);
	n->append_child() << ryml::key("num_mapped_outs") << std::to_string(ph.num_mapped_outs);
	n->append_child() << ryml::key("num_static_knobs") << std::to_string(ph.num_static_knobs);
	n->append_child() << ryml::key("num_mapped_knobs") << std::to_string(ph.num_mapped_knobs);
}

bool read(ryml::NodeRef const &n, _TestPatchHeader *ph) {
	if (n.num_children() != 8)
		return false;
	if (n.child(0).key() != "header_version")
		return false;
	if (n.child(1).key() != "patch_name")
		return false;
	if (n.child(2).key() != "num_modules")
		return false;
	//TODO: rest of fields...

	n["header_version"] >> ph->header_version;
	n["patch_name"] >> ph->patch_name;
	n["num_modules"] >> ph->num_modules;
	n["num_int_cables"] >> ph->num_int_cables;
	n["num_mapped_ins"] >> ph->num_mapped_ins;
	n["num_mapped_outs"] >> ph->num_mapped_outs;
	n["num_static_knobs"] >> ph->num_static_knobs;
	n["num_mapped_knobs"] >> ph->num_mapped_knobs;
	return true;
}

bool TEST_CASE_Can_create_a_rymlTree_from_a_PatchHeader_using_operator_lshift() {
	ryml::Tree tree;
	_TestPatchHeader ph_in{
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

	_TestPatchHeader ph_out;
	tree.rootref() >> ph_out;
	CHECK(ph_out.header_version == ph_in.header_version);
	CHECK(ph_out.patch_name.is_equal(ph_in.patch_name));
	CHECK(ph_out.num_modules == ph_in.num_modules);
	CHECK(ph_out.num_int_cables == ph_in.num_int_cables);
	CHECK(ph_out.num_mapped_ins == ph_in.num_mapped_ins);
	CHECK(ph_out.num_mapped_outs == ph_in.num_mapped_outs);
	CHECK(ph_out.num_static_knobs == ph_in.num_static_knobs);
	CHECK(ph_out.num_mapped_knobs == ph_in.num_mapped_knobs);

	return true;
}

bool TEST_CASE_Can_parse_patch_header_using_operator_rshift() {
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

	_TestPatchHeader ph_out;

	tree.rootref() >> ph_out;
	CHECK(ph_out.header_version == 1);
	CHECK(ph_out.patch_name.is_equal("test123"));
	CHECK(ph_out.num_modules == 4);
	CHECK(ph_out.num_int_cables == 5);
	CHECK(ph_out.num_mapped_ins == 6);
	CHECK(ph_out.num_mapped_outs == 7);
	CHECK(ph_out.num_static_knobs == 8);
	CHECK(ph_out.num_mapped_knobs == 9);

	return true;
}

bool TEST_CASE_Correct_header_and_data_produced_from_yaml() {
	std::string yamlhdr =
		// clang-format off
R"(PatchData:
  patch_name: 'Test Patch 99'
  module_slugs:
    0: PanelMedium
    1: Module1
    2: Module2
    3: Module3
  int_cables:
    - out:
        module_id: 1
        jack_id: 2
      ins:
        - module_id: 3
          jack_id: 4
        - module_id: 5
          jack_id: 6
    - out:
        module_id: 11
        jack_id: 22
      ins:
        - module_id: 33
          jack_id: 44
        - module_id: 55
          jack_id: 66
        - module_id: 77
          jack_id: 88
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 4
    - panel_jack_id: 2
      ins:
        - module_id: 5
          jack_id: 6
        - module_id: 33
          jack_id: 44
    - panel_jack_id: 3
      ins:
        - module_id: 77
          jack_id: 88
  mapped_outs:
    - panel_jack_id: 4
      out:
        module_id: 1
        jack_id: 2
    - panel_jack_id: 5
      out:
        module_id: 11
        jack_id: 22
  static_knobs:
    - module_id: 1
      param_id: 2
      value: 0.3
    - module_id: 2
      param_id: 3
      value: 0.4
    - module_id: 3
      param_id: 4
      value: 0.5
    - module_id: 4
      param_id: 5
      value: 0.6
    - module_id: 5
      param_id: 6
      value: 0.7
  mapped_knobs:
    - panel_knob_id: 1
      module_id: 2
      param_id: 3
      curve_type: 1
      min: 0.1
      max: 0.95
    - panel_knob_id: 0
      module_id: 3
      param_id: 4
      curve_type: 2
      min: 0.2
      max: 0.85
    - panel_knob_id: 3
      module_id: 4
      param_id: 5
      curve_type: 3
      min: 0.3
      max: 0.75
    - panel_knob_id: 3
      module_id: 5
      param_id: 6
      curve_type: 4
      min: 0.4
      max: 0.65
)";
	// clang-format on

	PatchData pd;
	CHECK(yaml_string_to_patch(yamlhdr, pd));

	CHECK(pd.patch_name.is_equal("Test Patch 99"));

	CHECK(pd.module_slugs.size() == 4);
	CHECK(pd.module_slugs[0].is_equal("PanelMedium"));
	CHECK(pd.module_slugs[1].is_equal("Module1"));
	CHECK(pd.module_slugs[2].is_equal("Module2"));
	CHECK(pd.module_slugs[3].is_equal("Module3"));

	CHECK(pd.int_cables.size() == 2);
	CHECK(pd.int_cables[0].out == (Jack{1, 2}));
	CHECK(pd.int_cables[0].ins[0] == (Jack{3, 4}));
	CHECK(pd.int_cables[0].ins[1] == (Jack{5, 6}));
	// CHECK(pd.int_cables[0].ins[2] == (Jack{-1, -1}));
	CHECK(pd.int_cables[1].out == (Jack{11, 22}));
	CHECK(pd.int_cables[1].ins[0] == (Jack{33, 44}));
	CHECK(pd.int_cables[1].ins[1] == (Jack{55, 66}));
	CHECK(pd.int_cables[1].ins[2] == (Jack{77, 88}));

	CHECK(pd.mapped_ins.size() == 3);
	CHECK(pd.mapped_ins[0].panel_jack_id == 1);
	CHECK(pd.mapped_ins[0].ins[0] == (Jack{3, 4}));
	// CHECK(pd.mapped_ins[0].ins[1] == (Jack{-1, -1}));
	CHECK(pd.mapped_ins[1].panel_jack_id == 2);
	CHECK(pd.mapped_ins[1].ins[0] == (Jack{5, 6}));
	CHECK(pd.mapped_ins[1].ins[1] == (Jack{33, 44}));
	// CHECK(pd.mapped_ins[1].ins[2] == (Jack{-1, -1}));
	CHECK(pd.mapped_ins[2].panel_jack_id == 3);
	CHECK(pd.mapped_ins[2].ins[0] == (Jack{77, 88}));
	// CHECK(pd.mapped_ins[2].ins[1] == (Jack{-1, -1}));

	CHECK(pd.mapped_outs.size() == 2);
	CHECK(pd.mapped_outs[0].panel_jack_id == 4);
	CHECK(pd.mapped_outs[0].out == (Jack{1, 2}));
	CHECK(pd.mapped_outs[1].panel_jack_id == 5);
	CHECK(pd.mapped_outs[1].out == (Jack{11, 22}));

	CHECK(pd.static_knobs.size() == 5);
	CHECK(pd.static_knobs[0].module_id == 1);
	CHECK(pd.static_knobs[0].param_id == 2);
	CHECK(pd.static_knobs[0].value == 0.3f);
	CHECK(pd.static_knobs[1].module_id == 2);
	CHECK(pd.static_knobs[1].param_id == 3);
	CHECK(pd.static_knobs[1].value == 0.4f);
	CHECK(pd.static_knobs[2].module_id == 3);
	CHECK(pd.static_knobs[2].param_id == 4);
	CHECK(pd.static_knobs[2].value == 0.5f);
	CHECK(pd.static_knobs[3].module_id == 4);
	CHECK(pd.static_knobs[3].param_id == 5);
	CHECK(pd.static_knobs[3].value == 0.6f);
	CHECK(pd.static_knobs[4].module_id == 5);
	CHECK(pd.static_knobs[4].param_id == 6);
	CHECK(pd.static_knobs[4].value == 0.7f);

	CHECK(pd.mapped_knobs.size() == 4);
	CHECK(pd.mapped_knobs[0].panel_knob_id == 1);
	CHECK(pd.mapped_knobs[0].module_id == 2);
	CHECK(pd.mapped_knobs[0].param_id == 3);
	CHECK(pd.mapped_knobs[0].curve_type == 1);
	CHECK(pd.mapped_knobs[0].min == 0.1f);
	CHECK(pd.mapped_knobs[0].max == 0.95f);
	CHECK(pd.mapped_knobs[1].panel_knob_id == 0);
	CHECK(pd.mapped_knobs[1].module_id == 3);
	CHECK(pd.mapped_knobs[1].param_id == 4);
	CHECK(pd.mapped_knobs[1].curve_type == 2);
	CHECK(pd.mapped_knobs[1].min == 0.2f);
	CHECK(pd.mapped_knobs[1].max == 0.85f);
	CHECK(pd.mapped_knobs[2].panel_knob_id == 3);
	CHECK(pd.mapped_knobs[2].module_id == 4);
	CHECK(pd.mapped_knobs[2].param_id == 5);
	CHECK(pd.mapped_knobs[2].curve_type == 3);
	CHECK(pd.mapped_knobs[2].min == 0.3f);
	CHECK(pd.mapped_knobs[2].max == 0.75f);
	CHECK(pd.mapped_knobs[3].panel_knob_id == 3);
	CHECK(pd.mapped_knobs[3].module_id == 5);
	CHECK(pd.mapped_knobs[3].param_id == 6);
	CHECK(pd.mapped_knobs[3].curve_type == 4);
	CHECK(pd.mapped_knobs[3].min == 0.4f);
	CHECK(pd.mapped_knobs[3].max == 0.65f);

	return true;
}
} // namespace

namespace PatchListTargetTests
{
bool run_all_tests() {
	if (!TEST_CASE_Correct_header_and_data_produced_from_yaml())
		return false;
	if (!TEST_CASE_Basic_hierarchal_YAML_Usage())
		return false;
	if (!TEST_CASE_Numbers_as_keys())
		return false;
	if (!TEST_CASE_Sequences())
		return false;
	if (!TEST_CASE_Sequences2())
		return false;
	if (!TEST_CASE_Can_return_a_NodeRef())
		return false;
	if (!TEST_CASE_Can_use_const_char_for_keys())
		return false;
	if (!TEST_CASE_Can_parse_a_struct_field_by_field())
		return false;
	if (!TEST_CASE_Can_create_a_rymlTree_from_a_PatchHeader_using_operator_lshift())
		return false;
	if (!TEST_CASE_Can_parse_patch_header_using_operator_rshift())
		return false;

	return true;
}
} // namespace PatchListTargetTests
