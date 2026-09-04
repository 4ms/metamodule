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

	player.update_patch();
	player.unload_patch();
}

