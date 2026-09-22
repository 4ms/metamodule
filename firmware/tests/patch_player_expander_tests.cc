#include "doctest.h"
#include "patch_play/patch_player.hh"
#include "yaml_to_patch.hh"
#include <string>

// PatchPlayer expander plumbing: load a patch with an `expanders` field and
// verify it loads and runs. The modules here are not rack::Module instances
// (NullModule/native), so the wiring must safely skip them — the actual
// pointer/message semantics are covered by expander_hookup_tests.cc, and
// end-to-end behavior with real rack modules is verified in the simulator.

TEST_CASE("patch with expanders field loads and runs safely") {
	// clang-format off
	std::string patchyml{R"(PatchData:
  patch_name: expander_plumbing_test
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'Befaco:PonyVCO'
    2: 'Befaco:PonyVCO'
  int_cables: []
  mapped_ins: []
  mapped_outs: []
  static_knobs: []
  mapped_knobs: []
  midi_maps:
    name: ''
    set: []
  expanders:
    - left_module_id: 1
      right_module_id: 2
)"};
	// clang-format on

	MetaModule::PatchData pd;
	REQUIRE(yaml_string_to_patch(patchyml, pd));
	REQUIRE(pd.expanders.size() == 1);

	MetaModule::PatchPlayer player;
	auto result = player.load_patch(pd);
	CHECK(result.success);

	// No rack modules in the test build, so nothing got wired:
	CHECK(player.expanders().num_connections() == 0);
	CHECK(player.expander_status({1, 2}) == MetaModule::PatchPlayer::ExpanderStatus::NotConnected);

	for (auto i = 0; i < 16; i++)
		player.update_patch();

	player.unload_patch();
}

TEST_CASE("removing a module keeps the remaining expanders and keeps running safely") {
	// clang-format off
	std::string patchyml{R"(PatchData:
  patch_name: expander_remove_test
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'Befaco:PonyVCO'
    2: 'Befaco:PonyVCO'
    3: 'Befaco:PonyVCO'
  int_cables: []
  mapped_ins: []
  mapped_outs: []
  static_knobs: []
  mapped_knobs: []
  midi_maps:
    name: ''
    set: []
  expanders:
    - left_module_id: 2
      right_module_id: 3
)"};
	// clang-format on

	MetaModule::PatchData pd;
	REQUIRE(yaml_string_to_patch(patchyml, pd));

	MetaModule::PatchPlayer player;
	REQUIRE(player.load_patch(pd).success);

	// Removing an unrelated module shifts the ids in the patch data
	// (id squash/erase is covered in patch-serial's tests)
	player.remove_module(1);

	// Removing a module in the pair removes the connection
	player.remove_module(2);
	CHECK(player.expanders().num_connections() == 0);

	for (auto i = 0; i < 16; i++)
		player.update_patch();

	player.unload_patch();
}

TEST_CASE("expanders with out-of-range module ids are ignored") {
	// clang-format off
	std::string patchyml{R"(PatchData:
  patch_name: expander_bounds_test
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'Befaco:PonyVCO'
  int_cables: []
  mapped_ins: []
  mapped_outs: []
  static_knobs: []
  mapped_knobs: []
  midi_maps:
    name: ''
    set: []
  expanders:
    - left_module_id: 1
      right_module_id: 99
    - left_module_id: 88
      right_module_id: 1
)"};
	// clang-format on

	MetaModule::PatchData pd;
	REQUIRE(yaml_string_to_patch(patchyml, pd));

	MetaModule::PatchPlayer player;
	auto result = player.load_patch(pd);
	CHECK(result.success);
	CHECK(player.expanders().num_connections() == 0);
	CHECK(player.expander_status({1, 99}) == MetaModule::PatchPlayer::ExpanderStatus::NotConnected);

	player.update_patch();
	player.unload_patch();
}

TEST_CASE("add_expander/remove_expander at runtime") {
	// clang-format off
	std::string patchyml{R"(PatchData:
  patch_name: expander_add_remove_test
  module_slugs:
    0: '4msCompany:HubMedium'
    1: 'Befaco:PonyVCO'
    2: 'Befaco:PonyVCO'
  int_cables: []
  mapped_ins: []
  mapped_outs: []
  static_knobs: []
  mapped_knobs: []
  midi_maps:
    name: ''
    set: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	REQUIRE(yaml_string_to_patch(patchyml, pd));

	MetaModule::PatchPlayer player;
	REQUIRE(player.load_patch(pd).success);

	// Invalid connections are rejected
	CHECK_FALSE(player.add_expander({1, 1}));
	CHECK_FALSE(player.add_expander({0, 1}));
	CHECK_FALSE(player.add_expander({1, 50}));

	// A valid pair of non-rack modules can't be wired, so it's rejected too
	CHECK_FALSE(player.add_expander({1, 2}));
	CHECK(player.expanders().num_connections() == 0);

	// Removing what isn't there is harmless
	CHECK_FALSE(player.remove_expander({1, 2}));

	player.update_patch();
	player.unload_patch();
}

TEST_CASE("patch_expanders helpers") {
	MetaModule::PatchData pd;
	pd.module_slugs = {"4msCompany:HubMedium", "A:a", "A:b", "A:c"};

	CHECK_FALSE(pd.find_expander(1, ExpanderSide::Right).has_value());

	CHECK(pd.add_expander({1, 2}));
	REQUIRE(pd.expanders.size() == 1);
	CHECK(pd.has_expander({1, 2}));
	CHECK_FALSE(pd.has_expander({2, 1}));

	// Lookups from either module's point of view
	CHECK(pd.find_expander_module(1, ExpanderSide::Right) == 2);
	CHECK(pd.find_expander_module(2, ExpanderSide::Left) == 1);
	CHECK_FALSE(pd.find_expander_module(1, ExpanderSide::Left).has_value());
	CHECK_FALSE(pd.find_expander_module(2, ExpanderSide::Right).has_value());

	// Each side of a module holds one expander
	CHECK_FALSE(pd.can_add_expander({1, 3}));
	CHECK_FALSE(pd.can_add_expander({3, 2}));
	CHECK(pd.can_add_expander({2, 3}));
	CHECK(pd.can_add_expander({3, 1}));

	// Rejects self, hub, and out-of-range
	CHECK_FALSE(pd.can_add_expander({3, 3}));
	CHECK_FALSE(pd.can_add_expander({0, 3}));
	CHECK_FALSE(pd.can_add_expander({3, 0}));
	CHECK_FALSE(pd.can_add_expander({3, 4}));

	// Rejects loops: with 1->2 in place, 2->1 would make a loop, and so would 3->1 once 2->3 exists
	CHECK_FALSE(pd.can_add_expander({2, 1}));
	CHECK(pd.expander_chain_reaches(1, ExpanderSide::Right, 2));
	CHECK_FALSE(pd.expander_chain_reaches(2, ExpanderSide::Right, 1));
	CHECK(pd.add_expander({2, 3}));
	CHECK(pd.expander_chain_reaches(1, ExpanderSide::Right, 3));
	CHECK(pd.expander_chain_reaches(3, ExpanderSide::Left, 1));
	CHECK_FALSE(pd.can_add_expander({3, 1}));
	CHECK(pd.remove_expander({2, 3}));

	// Building a connection from a module + side + other module
	auto conn = ExpanderConnection::make(3, ExpanderSide::Left, 2);
	CHECK(conn.left_module_id == 2);
	CHECK(conn.right_module_id == 3);
	conn = ExpanderConnection::make(3, ExpanderSide::Right, 1);
	CHECK(conn.left_module_id == 3);
	CHECK(conn.right_module_id == 1);

	CHECK(pd.remove_expander({1, 2}));
	CHECK_FALSE(pd.remove_expander({1, 2}));
	CHECK(pd.expanders.size() == 0);
}
