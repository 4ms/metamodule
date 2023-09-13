#include "doctest.h"
#include "patch_convert/yaml_to_patch.hh"

#define printf_ printf

#include "patch_play/patch_player.hh"
#include <string>

TEST_CASE("Simple output jack mapping") {
	std::string patchyml{// clang-format off
R"(PatchData:
  patch_name: unittest_outmap
  module_slugs:
    0: PANEL_8
    1: MULTILFO
    2: MULTILFO
  int_cables: 
  mapped_ins: 
  mapped_outs: 
    - panel_jack_id: 1
      out: 
        module_id: 1
        jack_id: 1
    - panel_jack_id: 0
      out: 
        module_id: 1
        jack_id: 3
    - panel_jack_id: 2
      out: 
        module_id: 2
        jack_id: 1
  static_knobs: 
  mapped_knobs: 
  midi_maps:
)"};
						 // clang-format on
	PatchData pd;
	CHECK(yaml_string_to_patch(patchyml, pd));

	MetaModule::PatchPlayer player;
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	REQUIRE(pd.mapped_outs.size() == 3);

	SUBCASE("Check if mapped_outs[] data was loaded OK") {
		SUBCASE("Check if output connection data is correct") {
			CHECK(player.get_panel_output_connection(0) == Jack{1, 3});
			CHECK(player.get_panel_output_connection(1) == Jack{1, 1});
			CHECK(player.get_panel_output_connection(2) == Jack{2, 1});

			SUBCASE("Unmapped jacks are connected to 0,0") {
				CHECK(player.get_panel_output_connection(3) == Jack{0, 0});
				CHECK(player.get_panel_output_connection(4) == Jack{0, 0});
			}
		}
	}
}

TEST_CASE("Internal cables: single and stacked") {
	// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: unittest_outmap_overlapping_cab
  module_slugs:
    0: PANEL_8
    1: MULTILFO
    2: MULTILFO
  int_cables: 
      - out: 
          module_id: 1
          jack_id: 3
        ins: 
          - module_id: 2
            jack_id: 0
      - out: 
          module_id: 1
          jack_id: 1
        ins: 
          - module_id: 2
            jack_id: 1
          - module_id: 2
            jack_id: 2
  mapped_ins: 
  mapped_outs: 
    - panel_jack_id: 1
      out: 
        module_id: 1
        jack_id: 1
    - panel_jack_id: 0
      out: 
        module_id: 1
        jack_id: 3
    - panel_jack_id: 2
      out: 
        module_id: 2
        jack_id: 1
  static_knobs: 
  mapped_knobs: 
  midi_maps:
	)"};
	// clang-format on

	PatchData pd;
	CHECK(yaml_string_to_patch(patchyml, pd));

	// In VCV Rack, if two cables are stacked, they appear as two separate cables.
	// Contrary to this, we consider them as a single cable, with one output and two inputs.
	// So, this patch should have 2 cables (a 1->1 and a 1->2)
	CHECK(pd.int_cables.size() == 2);

	MetaModule::PatchPlayer player;
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	bool found_cable1 = false;
	bool found_cable2 = false;
	int cable1_idx = -1;
	int cable2_idx = -1;

	for (int net_i = 0; net_i < (int)pd.int_cables.size(); net_i++) {
		auto &cable = player.get_int_cable(net_i);

		// Check for cable1: 1->1 cable
		// {1,3} -> {2,0}
		if (cable.out == Jack{1, 3}) {
			if (cable.ins[0] == Jack{2, 0}) {
				if (cable.ins.size() == 1) {
					found_cable1 = true;
					cable1_idx = net_i;
				}
			}
		}

		// Check for cable2: 1->2 cable
		// {1,1} -> {2,1},{2,2}  or  {2,2},{2,1}
		if (cable.out == Jack{1, 1}) {
			if ((cable.ins[0] == Jack{2, 1} && cable.ins[1] == Jack{2, 2}) ||
				(cable.ins[0] == Jack{2, 2} && cable.ins[1] == Jack{2, 1}))
			{
				if (cable.ins.size() == 2) {
					found_cable2 = true;
					cable2_idx = net_i;
				}
			}
		}
	}

	SUBCASE("Check both cables were found") {
		CHECK(found_cable1);
		CHECK(found_cable2);

		SUBCASE("Check cables have the correct number of input jacks") {
			CHECK(player.get_num_int_cable_ins(cable1_idx) == 1);
			CHECK(player.get_num_int_cable_ins(cable2_idx) == 2);
		}
	}

	SUBCASE("It's OK to have a Panel output jack mapping to an virtual input jack that has a valid cable") {
		CHECK(pd.mapped_outs.size() == 3);

		SUBCASE("Check if output connection data is correct") {
			// printf("player.get_panel_output_connection(0) == Jack{%d, %d}\n",
			// 	   player.get_panel_output_connection(0).jack_id,
			// 	   player.get_panel_output_connection(0).module_id);
			// printf("player.get_panel_output_connection(1) == Jack{%d, %d}\n",
			// 	   player.get_panel_output_connection(1).jack_id,
			// 	   player.get_panel_output_connection(1).module_id);
			// printf("player.get_panel_output_connection(2) == Jack{%d, %d}\n",
			// 	   player.get_panel_output_connection(2).jack_id,
			// 	   player.get_panel_output_connection(2).module_id);

			CHECK(player.get_panel_output_connection(0) == Jack{1, 3});
			CHECK(player.get_panel_output_connection(1) == Jack{1, 1});
			CHECK(player.get_panel_output_connection(2) == Jack{2, 1});

			SUBCASE("Unmapped jack is connected to -1,-1") {
				CHECK(player.get_panel_output_connection(3) == Jack{0, 0});
				CHECK(player.get_panel_output_connection(4) == Jack{0, 0});
			}
		}
	}
}

//#include "patches/unittest_inmapping.hh"
// Note: we do not support multiple input mappings in VCV (yet), so aren't testing for it now
// because there's no easy way to create the test data
TEST_CASE("Simple input jack mapping") {
	// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: unittest_inmapping
  module_slugs:
    0: PANEL_8
    1: MIXER4
    2: KARPLUS
  int_cables: 
  mapped_ins: 
      - panel_jack_id: 0
        ins: 
          - module_id: 1
            jack_id: 0
      - panel_jack_id: 1
        ins: 
          - module_id: 1
            jack_id: 2
      - panel_jack_id: 2
        ins: 
          - module_id: 2
            jack_id: 1
      - panel_jack_id: 3
        ins: 
          - module_id: 2
            jack_id: 0
      - panel_jack_id: 6
        ins: 
          - module_id: 1
            jack_id: 1
      - panel_jack_id: 7
        ins: 
          - module_id: 1
            jack_id: 3
  mapped_outs: 
  static_knobs: 
  mapped_knobs: 
	)"};
	// clang-format on

	PatchData pd;

	MetaModule::PatchPlayer player;
	yaml_string_to_patch(patchyml, pd);
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	REQUIRE(pd.mapped_ins.size() == 6);

	SUBCASE("Check if input connection data is correct") {
		CHECK(player.get_panel_input_connection(0) == Jack{1, 0});
		CHECK(player.get_panel_input_connection(1) == Jack{1, 2});
		CHECK(player.get_panel_input_connection(2) == Jack{2, 1});
		CHECK(player.get_panel_input_connection(3) == Jack{2, 0});
		CHECK(player.get_panel_input_connection(6) == Jack{1, 1});
		CHECK(player.get_panel_input_connection(7) == Jack{1, 3});

		SUBCASE("Unmapped jacks are connected to 0,0") {
			CHECK(player.get_panel_input_connection(4) == Jack{0, 0});
			CHECK(player.get_panel_input_connection(5) == Jack{0, 0});

			SUBCASE("All connections are 1->1") {
				CHECK(player.get_panel_input_connection(0, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(1, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(2, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(3, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(4, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(5, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(6, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(7, 1) == Jack{0, 0});
				CHECK(player.get_panel_input_connection(8, 1) == Jack{0, 0});
			}
		}
	}
}
#include "patches/unittest_inmapping_overlapping.hh"
TEST_CASE("Input jack is patched and mapped to a panel jack -- for now we ignore the mapping") {
	// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: unittest_inmapping_overlapping
  module_slugs:
    0: PANEL_8
    1: MULTILFO
    2: LFOSINE
  int_cables: 
      - out: 
          module_id: 2
          jack_id: 0
        ins: 
          - module_id: 1
            jack_id: 0
  mapped_ins: 
      - panel_jack_id: 2
        ins: 
          - module_id: 1
            jack_id: 0
  mapped_outs: 
  static_knobs: 
  mapped_knobs: 
  midi_maps:
	)"};
	// clang-format on

	PatchData pd;

	MetaModule::PatchPlayer player;
	yaml_string_to_patch(patchyml, pd);
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	REQUIRE(pd.mapped_ins.size() == 1);
	REQUIRE(pd.int_cables.size() == 1);

	SUBCASE("No input mappings are present") {
		CHECK(player.get_panel_input_connection(0) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(1) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(2) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(3) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(4) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(5) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(6) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(7) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(8) == Jack{0, 0});

		SUBCASE("Internal cable is still present") {
			CHECK(player.get_int_cable(0).out == Jack{2, 0});
			CHECK(player.get_num_int_cable_ins(0) == 1);
			CHECK(player.get_int_cable(0).ins[0] == Jack{1, 0});
		}
	}
}

//#include "patches/unittest_dup_mod_index.hh"
TEST_CASE("Dup module index") {
	SUBCASE("If there's more than one of a module type, get the correct 'dup index' for each") {
		// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: unittest_dup_mod_index
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: KARPLUS
    3: LFOSINE
    4: CLKMULTIPLIER
    5: LFOSINE
    6: LFOSINE
    7: KARPLUS
  int_cables: 
  mapped_ins: 
  mapped_outs: 
  static_knobs: 
  mapped_knobs: 
  midi_maps:
	)"};
		// clang-format on

		PatchData pd;

		MetaModule::PatchPlayer player;
		yaml_string_to_patch(patchyml, pd);
		player.copy_patch_data(pd);
		player.calc_multiple_module_indicies();

		REQUIRE(pd.module_slugs.size() == 8);
		CHECK(player.get_multiple_module_index(0) == 0); // PANEL_8
		CHECK(player.get_multiple_module_index(1) == 1); // LFOSINE 1
		CHECK(player.get_multiple_module_index(2) == 1); // KARPLUS 1
		CHECK(player.get_multiple_module_index(3) == 2); // LFOSINE 2
		CHECK(player.get_multiple_module_index(4) == 0); // CLOCK
		CHECK(player.get_multiple_module_index(5) == 3); // LFOSINE 3
		CHECK(player.get_multiple_module_index(6) == 4); // LFOSINE 4
		CHECK(player.get_multiple_module_index(7) == 2); // KARPLUS 2

		SUBCASE("Unloading a patch clears the indices to 0") {
			player.unload_patch();
			CHECK(player.get_multiple_module_index(0) == 0);
			CHECK(player.get_multiple_module_index(1) == 0);
			CHECK(player.get_multiple_module_index(2) == 0);
			CHECK(player.get_multiple_module_index(3) == 0);
			CHECK(player.get_multiple_module_index(4) == 0);
			CHECK(player.get_multiple_module_index(5) == 0);
			CHECK(player.get_multiple_module_index(6) == 0);
			CHECK(player.get_multiple_module_index(7) == 0);
		}
	}
}
