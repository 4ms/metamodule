#include "doctest.h"
#include "patch-serial/patch_to_yaml.hh"
#include "patch-serial/yaml_to_patch.hh"

#include "patch_play/patch_player.hh"
#include <fstream>
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
  midi_poly_num: 1
)"};
						 // clang-format on
	MetaModule::PatchData pd;
	CHECK(yaml_string_to_patch(patchyml, pd));

	MetaModule::PatchPlayer player;
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	CHECK(pd.mapped_outs.size() == 3);

	SUBCASE("Check if mapped_outs[] data was loaded OK") {
		SUBCASE("Check if output connection data is correct") {
			CHECK(player.get_panel_output_connection(0) == Jack{1, 3});
			CHECK(player.get_panel_output_connection(1) == Jack{1, 1});
			CHECK(player.get_panel_output_connection(2) == Jack{2, 1});

			SUBCASE("Unmapped jacks are connected to 0xFFFF,0xFFFF") {
				CHECK(player.get_panel_output_connection(3) == Jack{0xFFFF, 0xFFFF});
				CHECK(player.get_panel_output_connection(4) == Jack{0xFFFF, 0xFFFF});
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
  midi_poly_num: 1
	)"};
	// clang-format on

	MetaModule::PatchData pd;
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
				CHECK(player.get_panel_output_connection(3) == Jack{0xFFFF, 0xFFFF});
				CHECK(player.get_panel_output_connection(4) == Jack{0xFFFF, 0xFFFF});
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

	MetaModule::PatchData pd;

	MetaModule::PatchPlayer player;
	yaml_string_to_patch(patchyml, pd);
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	CHECK(pd.mapped_ins.size() == 6);

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

	CHECK(pd.midi_maps.set.size() == 0);
	CHECK(pd.midi_maps.name.size() == 0);
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

	MetaModule::PatchData pd;

	MetaModule::PatchPlayer player;
	yaml_string_to_patch(patchyml, pd);
	player.copy_patch_data(pd);
	player.calc_panel_jack_connections();

	CHECK(pd.mapped_ins.size() == 1);
	CHECK(pd.int_cables.size() == 1);

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

	CHECK(pd.midi_maps.set.size() == 0);
	CHECK(pd.midi_maps.name.size() == 0);
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

		MetaModule::PatchData pd;

		MetaModule::PatchPlayer player;
		yaml_string_to_patch(patchyml, pd);
		player.copy_patch_data(pd);
		player.calc_multiple_module_indicies();

		CHECK(pd.module_slugs.size() == 8);
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

TEST_CASE("Knob and MIDI Maps") {
	// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: Knob and MIDI Map Test
  module_slugs:
    0: PANEL_8
    1: MULTILFO
    2: LFOSINE
  int_cables: []
  mapped_ins: [] 
  mapped_outs: []
  static_knobs: []
  mapped_knobs:
    - name: 'Set 1'
      set:
        - panel_knob_id: 1
          module_id: 5
          param_id: 4
          curve_type: 0
          min: 0
          max: 1
    - name: 'Set 2'
      set:
        - panel_knob_id: 20
          module_id: 25
          param_id: 24
          curve_type: 0
          min: 20
          max: 21
    - name: 'Set 3'
      set:
        - panel_knob_id: 30
          module_id: 35
          param_id: 34
          curve_type: 0
          min: 30
          max: 31
        - panel_knob_id: 40
          module_id: 45
          param_id: 44
          curve_type: 0
          min: 40
          max: 41
  midi_maps:
    name: MIDI
    set:
      - panel_knob_id: 522 
        module_id: 1
        param_id: 9
        curve_type: 0
        min: 0.1
        max: .9
      - panel_knob_id: 586
        module_id: 5
        param_id: 3
        curve_type: 0
        min: 0.75
        max: 0.25 
	)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	CHECK(pd.knob_sets.size() == 3);

	CHECK(pd.knob_sets[0].name.is_equal("Set 1"));
	CHECK(pd.knob_sets[0].set.size() == 1);
	CHECK(pd.knob_sets[0].set[0].panel_knob_id == 1);
	CHECK(pd.knob_sets[0].set[0].module_id == 5);
	CHECK(pd.knob_sets[0].set[0].min == 0);
	CHECK(pd.knob_sets[0].set[0].max == 1);

	CHECK(pd.knob_sets[1].name.is_equal("Set 2"));
	CHECK(pd.knob_sets[1].set.size() == 1);
	CHECK(pd.knob_sets[1].set[0].panel_knob_id == 20);
	CHECK(pd.knob_sets[1].set[0].module_id == 25);
	CHECK(pd.knob_sets[1].set[0].param_id == 24);
	CHECK(pd.knob_sets[1].set[0].min == 20);
	CHECK(pd.knob_sets[1].set[0].max == 21);

	CHECK(pd.knob_sets[2].name.is_equal("Set 3"));
	CHECK(pd.knob_sets[2].set.size() == 2);
	CHECK(pd.knob_sets[2].set[0].panel_knob_id == 30);
	CHECK(pd.knob_sets[2].set[0].module_id == 35);
	CHECK(pd.knob_sets[2].set[0].param_id == 34);
	CHECK(pd.knob_sets[2].set[0].min == 30);
	CHECK(pd.knob_sets[2].set[0].max == 31);
	CHECK(pd.knob_sets[2].set[1].panel_knob_id == 40);
	CHECK(pd.knob_sets[2].set[1].module_id == 45);
	CHECK(pd.knob_sets[2].set[1].param_id == 44);
	CHECK(pd.knob_sets[2].set[1].min == 40);
	CHECK(pd.knob_sets[2].set[1].max == 41);

	CHECK(pd.midi_maps.set.size() == 2);
	CHECK(pd.midi_maps.name.size() == 4);
	CHECK(pd.midi_maps.set[0].panel_knob_id == 522);
	CHECK(pd.midi_maps.set[0].module_id == 1);
	CHECK(pd.midi_maps.set[0].param_id == 9);
	CHECK(pd.midi_maps.set[0].min == doctest::Approx(0.1));
	CHECK(pd.midi_maps.set[0].max == doctest::Approx(0.9));

	CHECK(pd.midi_maps.set[1].panel_knob_id == 586);
	CHECK(pd.midi_maps.set[1].module_id == 5);
	CHECK(pd.midi_maps.set[1].param_id == 3);
	CHECK(pd.midi_maps.set[1].min == doctest::Approx(0.75));
	CHECK(pd.midi_maps.set[1].max == doctest::Approx(0.25));
}

TEST_CASE("Blank out a module: remove all mappings and cables but don't change module indices") {
	// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: RemoveModuleTest
  description: Patch Description
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:StMix'
    2: '4msCompany:Drum'
    3: '4msCompany:MultiLFO'
  int_cables:
    - out:
        module_id: 3
        jack_id: 2
      ins:
        - module_id: 2
          jack_id: 3
      color: 35419
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 2
          jack_id: 4
        - module_id: 3
          jack_id: 3
      color: 65535
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
        - module_id: 2
          jack_id: 5
      color: 13501
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 3
          jack_id: 1
    - panel_jack_id: 1
      ins:
        - module_id: 3
          jack_id: 2
        - module_id: 2
          jack_id: 2
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 3
        jack_id: 1
    - panel_jack_id: 1
      out:
        module_id: 3
        jack_id: 3
    - panel_jack_id: 2
      out:
        module_id: 3
        jack_id: 3
    - panel_jack_id: 3
      out:
        module_id: 3
        jack_id: 2
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.5
    - module_id: 1
      param_id: 1
      value: 0.875
    - module_id: 1
      param_id: 2
      value: 0.875
    - module_id: 1
      param_id: 3
      value: 0.875
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 1
      param_id: 7
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.25
    - module_id: 2
      param_id: 1
      value: 0.25
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0.5
    - module_id: 2
      param_id: 4
      value: 0.25
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0.25
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 8
      value: 0
    - module_id: 3
      param_id: 0
      value: 0.5
    - module_id: 3
      param_id: 1
      value: 0.160241
    - module_id: 3
      param_id: 2
      value: 0.5
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 3
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 3
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	pd.blank_out_module(3);

	auto patchyml2 = patch_to_yaml_string(pd);

	// clang-format on
	CHECK(patchyml2 == R"(PatchData:
  patch_name: RemoveModuleTest
  description: Patch Description
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:StMix'
    2: '4msCompany:Drum'
    3: Blank
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 5
      color: 13501
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 2
  mapped_outs: []
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.5
    - module_id: 1
      param_id: 1
      value: 0.875
    - module_id: 1
      param_id: 2
      value: 0.875
    - module_id: 1
      param_id: 3
      value: 0.875
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 1
      param_id: 7
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.25
    - module_id: 2
      param_id: 1
      value: 0.25
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0.5
    - module_id: 2
      param_id: 4
      value: 0.25
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0.25
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 8
      value: 0
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates: []
)"
		  // clang-format off
		 );
}

TEST_CASE("Remove a module in the middle") {
	// clang-format off
	std::string patchyml{R"( 
PatchData:
  patch_name: RemoveModuleTest
  description: Patch Description
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:StMix'
    2: '4msCompany:MultiLFO'
    3: '4msCompany:Drum'
  int_cables:
    - out:
        module_id: 2
        jack_id: 2
      ins:
        - module_id: 3
          jack_id: 3
      color: 35419
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
        - module_id: 3
          jack_id: 4
        - module_id: 2
          jack_id: 3
      color: 65535
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 3
          jack_id: 5
      color: 13501
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 1
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 2
        - module_id: 3
          jack_id: 2
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 2
        jack_id: 1
    - panel_jack_id: 1
      out:
        module_id: 2
        jack_id: 3
    - panel_jack_id: 2
      out:
        module_id: 2
        jack_id: 3
    - panel_jack_id: 3
      out:
        module_id: 2
        jack_id: 2
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.5
    - module_id: 1
      param_id: 1
      value: 0.875
    - module_id: 1
      param_id: 2
      value: 0.875
    - module_id: 1
      param_id: 3
      value: 0.875
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 1
      param_id: 7
      value: 0.5
    - module_id: 3
      param_id: 0
      value: 0.25
    - module_id: 3
      param_id: 1
      value: 0.25
    - module_id: 3
      param_id: 2
      value: 0
    - module_id: 3
      param_id: 3
      value: 0.5
    - module_id: 3
      param_id: 4
      value: 0.25
    - module_id: 3
      param_id: 5
      value: 0
    - module_id: 3
      param_id: 6
      value: 0.25
    - module_id: 3
      param_id: 7
      value: 0
    - module_id: 3
      param_id: 8
      value: 0
    - module_id: 2
      param_id: 0
      value: 0.5
    - module_id: 2
      param_id: 1
      value: 0.160241
    - module_id: 2
      param_id: 2
      value: 0.5
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 2
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
        - panel_knob_id: 1
          module_id: 2
          param_id: 2
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	pd.remove_module(2);

	auto patchyml2 = patch_to_yaml_string(pd);

	// clang-format off
	CHECK(patchyml2 == R"(PatchData:
  patch_name: RemoveModuleTest
  description: Patch Description
  module_slugs:
    0: '4msCompany:HubMedium'
    1: '4msCompany:StMix'
    2: '4msCompany:Drum'
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 5
      color: 13501
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 2
  mapped_outs: []
  static_knobs:
    - module_id: 1
      param_id: 0
      value: 0.5
    - module_id: 1
      param_id: 1
      value: 0.875
    - module_id: 1
      param_id: 2
      value: 0.875
    - module_id: 1
      param_id: 3
      value: 0.875
    - module_id: 1
      param_id: 4
      value: 0.5
    - module_id: 1
      param_id: 5
      value: 0.5
    - module_id: 1
      param_id: 6
      value: 0.5
    - module_id: 1
      param_id: 7
      value: 0.5
    - module_id: 2
      param_id: 0
      value: 0.25
    - module_id: 2
      param_id: 1
      value: 0.25
    - module_id: 2
      param_id: 2
      value: 0
    - module_id: 2
      param_id: 3
      value: 0.5
    - module_id: 2
      param_id: 4
      value: 0.25
    - module_id: 2
      param_id: 5
      value: 0
    - module_id: 2
      param_id: 6
      value: 0.25
    - module_id: 2
      param_id: 7
      value: 0
    - module_id: 2
      param_id: 8
      value: 0
  mapped_knobs:
    - name: ''
      set:
        - panel_knob_id: 0
          module_id: 1
          param_id: 0
          curve_type: 0
          min: 0
          max: 1
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
    - name: ''
      set: []
  midi_maps:
    name: ''
    set: []
  midi_poly_num: 0
  vcvModuleStates: []
)");
	// clang-format on
}

TEST_CASE("Patchplayer works to delete a module in the middle") {
	std::ifstream ifs("tests/patches/DeleteTest.yml", std::ios::in);
	std::string patchyml((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	// printf("Patch:\n%s\n", patchyml.c_str());

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer p;
	p.load_patch(pd);

	// not used, but helpful for debugging
	[[maybe_unused]] auto dump = [&p]() {
		auto &modules = p.get_modules();
		auto slugs = p.get_module_slugs();

		for (unsigned i = 0; auto &mod : modules) {
			if (mod.get() != nullptr) {
				printf("MOD %d = %p (%s?)\n", i, mod.get(), slugs[i].c_str());
			}
			i++;
		}

		auto in_conns = p.get_inconns();
		for (unsigned i = 0; auto conn : in_conns) {
			printf("IN %d <- ", i);
			for (auto &in : conn)
				printf("%d,%d ", in.module_id, in.jack_id);
			printf("\n");
			i++;
		}

		auto out_conns = p.get_outconns();
		for (unsigned i = 0; auto out : out_conns) {
			printf("OUT %d <- ", i);
			printf("%d,%d ", out.module_id, out.jack_id);
			printf("\n");
			i++;
		}

		auto int_cables = p.get_int_cables();
		for (auto &cable : int_cables) {
			printf("%d,%d -> ", cable.out.module_id, cable.out.jack_id);
			for (auto in : cable.ins)
				printf("%d,%d ", in.module_id, in.jack_id);
			printf("\n");
		}
	};

	auto orig_mod1_ptr = p.get_modules()[1].get();
	auto orig_mod3_ptr = p.get_modules()[3].get();
	auto orig_mod1_slug = p.get_module_slugs()[1];
	auto orig_mod3_slug = p.get_module_slugs()[3];
	auto orig_panel_in_0_conns = p.get_inconns()[0];

	CHECK(orig_panel_in_0_conns[1].module_id == 3);
	CHECK(p.get_outconns()[0].module_id == 1);
	CHECK(p.get_outconns()[1].module_id == 2);

	// Original: 2 cables
	auto orig_num_int_cables = p.get_int_cables().size();

	// Cable 1 goes to module 2, so it will be removed
	CHECK(p.get_int_cables()[0].ins[0].module_id == 2);

	// Cable 2 goes to module 1 and 2, so only the part to module 2 will be removed
	auto orig_cable_out = p.get_int_cables()[1].out;

	auto orig_cable_num_ins = p.get_int_cables()[1].ins.size();
	auto orig_cable_in0 = p.get_int_cables()[1].ins[0];

	// dump();
	p.remove_module(2);
	// dump();

	// module 1 is the still module 1
	CHECK(orig_mod1_ptr == p.get_modules()[1].get());
	CHECK(orig_mod1_slug == p.get_module_slugs()[1]);

	// module 3 has become module 2
	CHECK(orig_mod3_ptr == p.get_modules()[2].get());
	CHECK(orig_mod3_slug == p.get_module_slugs()[2]);

	auto new_panel_in_0_conns = p.get_inconns()[0];
	// same as before
	CHECK(new_panel_in_0_conns[0] == orig_panel_in_0_conns[0]);
	// module 3 => 2
	CHECK(new_panel_in_0_conns[1].module_id == 2);

	CHECK(p.get_outconns()[0].module_id == 1);
	CHECK(p.get_outconns()[1].module_id == 0xFFFF); //disconnected

	CHECK(p.get_int_cables().size() == orig_num_int_cables - 1);
	CHECK(p.get_int_cables()[0].out.module_id == orig_cable_out.module_id - 1);
	CHECK(p.get_int_cables()[0].out.jack_id == orig_cable_out.jack_id);
	// Only one
	CHECK(p.get_int_cables()[0].ins.size() == orig_cable_num_ins - 1);
	CHECK(p.get_int_cables()[0].ins[0].module_id == orig_cable_in0.module_id);
	CHECK(p.get_int_cables()[0].ins[0].jack_id == orig_cable_in0.jack_id);
}
