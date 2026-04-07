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
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
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

			SUBCASE("Unmapped jacks have no connections") {
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
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
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

			SUBCASE("Unmapped jacks have no connections") {
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
TEST_CASE("Input jack is patched and mapped to a panel jack -- panel value routes through Hub for summing") {
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

	SUBCASE("Panel input 2 is routed to Hub for summing, others are unmapped") {
		CHECK(player.get_panel_input_connection(0) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(1) == Jack{0, 0});
		CHECK(player.get_panel_input_connection(2) == Jack{0, 2}); // routed to Hub jack 2
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
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
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
  mapped_lights: []
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
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
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
		for (unsigned i = 0; auto &outs : out_conns) {
			printf("OUT %d <- ", i);
			for (auto &out : outs)
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
	CHECK(p.get_outconns()[0][0].module_id == 1);
	CHECK(p.get_outconns()[1][0].module_id == 2);

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

	CHECK(p.get_outconns()[0][0].module_id == 1);
	CHECK(p.get_outconns()[1].size() == 0); //disconnected

	CHECK(p.get_int_cables().size() == orig_num_int_cables - 1);
	CHECK(p.get_int_cables()[0].out.module_id == orig_cable_out.module_id - 1);
	CHECK(p.get_int_cables()[0].out.jack_id == orig_cable_out.jack_id);
	// Only one
	CHECK(p.get_int_cables()[0].ins.size() == orig_cable_num_ins - 1);
	CHECK(p.get_int_cables()[0].ins[0].module_id == orig_cable_in0.module_id);
	CHECK(p.get_int_cables()[0].ins[0].jack_id == orig_cable_in0.jack_id);
}

// ============================================================================
// Summing tests
// ============================================================================

TEST_CASE("Summed internal cables: two outputs to same input") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: summed_int_cables
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: LFOSINE
    3: MULTILFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 3
          jack_id: 0
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Cable cache has a summed input for module 3 jack 0") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{3, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
				}
			}
		}
		CHECK(found);
	}

	SUBCASE("Summed entry contains both output jacks") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{3, 0}) {
					found = true;
					bool has_lfo1 = false, has_lfo2 = false;
					for (size_t j = 0; j < si.outs.size(); j++) {
						if (si.outs[j] == Jack{1, 0})
							has_lfo1 = true;
						if (si.outs[j] == Jack{2, 0})
							has_lfo2 = true;
					}
					CHECK(has_lfo1);
					CHECK(has_lfo2);
				}
			}
		}
		CHECK(found);
	}

	SUBCASE("Summed input is removed from regular cable arrays") {
		// Module 3 jack 0 should NOT appear in samecore or diffcore cable ins
		for (auto &core_cables : player.cables.samecore_cables) {
			for (auto &cable : core_cables) {
				for (size_t i = 0; i < cable.ins.size(); i++) {
					CHECK_FALSE((cable.ins[i] == Jack{3, 0}));
				}
			}
		}
		for (auto &core_cables : player.cables.diffcore_cables) {
			for (auto &cable : core_cables) {
				for (size_t i = 0; i < cable.ins.size(); i++) {
					CHECK_FALSE((cable.ins[i] == Jack{3, 0}));
				}
			}
		}
	}
}

TEST_CASE("Single internal cable: no summed input entry created") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: single_cable
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: MULTILFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("No summed inputs exist") {
		for (auto &core_si : player.cables.summed_inputs) {
			CHECK(core_si.size() == 0);
		}
	}
}

TEST_CASE("Summed panel output: two module outputs to same panel out jack") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: summed_panel_out
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: LFOSINE
  int_cables:
  mapped_ins:
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
    - panel_jack_id: 0
      out:
        module_id: 2
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Panel out 0 has two connections") {
		CHECK(player.get_outconns()[0].size() == 2);
		CHECK(player.get_panel_output_connection(0, 0) == Jack{1, 0});
		CHECK(player.get_panel_output_connection(0, 1) == Jack{2, 0});
	}

	SUBCASE("Panel out 0 sums the two module outputs") {
		// Run some frames
		for (int i = 0; i < 100; i++)
			player.update_patch();

		float lfo1 = player.modules[1]->get_output(0);
		float lfo2 = player.modules[2]->get_output(0);
		float panel_out = player.get_panel_output(0);

		CHECK(panel_out == doctest::Approx(lfo1 + lfo2));
	}

	SUBCASE("Other panel outs are unaffected") {
		CHECK(player.get_outconns()[1].size() == 0);
		CHECK(player.get_outconns()[2].size() == 0);
	}
}

TEST_CASE("Hub-to-Hub summing: multiple panel inputs to one panel output") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: hub_sum
  module_slugs:
    0: PANEL_8
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 0
    - panel_jack_id: 1
      ins:
        - module_id: 0
          jack_id: 0
    - panel_jack_id: 2
      ins:
        - module_id: 0
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Panel out 0 has three Hub output connections (one per panel input)") {
		CHECK(player.get_outconns()[0].size() == 3);
		CHECK(player.get_panel_output_connection(0, 0) == Jack{0, 0}); // Hub out 0 = panel in 0
		CHECK(player.get_panel_output_connection(0, 1) == Jack{0, 1}); // Hub out 1 = panel in 1
		CHECK(player.get_panel_output_connection(0, 2) == Jack{0, 2}); // Hub out 2 = panel in 2
	}

	SUBCASE("Panel inputs are NOT routed to Hub via in_conns (to avoid overwrite)") {
		// Hub-to-Hub connections skip in_conns entirely
		CHECK(player.get_inconns()[0].size() == 0);
		CHECK(player.get_inconns()[1].size() == 0);
		CHECK(player.get_inconns()[2].size() == 0);
	}

	SUBCASE("get_panel_output sums panel_in_vals for Hub connections") {
		player.set_panel_input(0, 1.0f);
		player.set_panel_input(1, 2.0f);
		player.set_panel_input(2, 3.0f);

		float panel_out = player.get_panel_output(0);
		CHECK(panel_out == doctest::Approx(1.0f + 2.0f + 3.0f));
	}
}

TEST_CASE("Panel input summed with internal cable") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: panel_plus_cable
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: MULTILFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Panel input 0 routes to Hub (not directly to module 2)") {
		// in_conns[0] should contain Hub connection, not module 2
		CHECK(player.get_panel_input_connection(0) == Jack{0, 0});
	}

	SUBCASE("Virtual cable creates a summed input for module 2 jack 0") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{2, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
					// Should have both the real cable (module 1 out 0) and virtual cable (Hub out 0)
					bool has_lfo = false, has_hub = false;
					for (size_t j = 0; j < si.outs.size(); j++) {
						if (si.outs[j] == Jack{1, 0})
							has_lfo = true;
						if (si.outs[j] == Jack{0, 0})
							has_hub = true;
					}
					CHECK(has_lfo);
					CHECK(has_hub);
				}
			}
		}
		CHECK(found);
	}

	SUBCASE("Module 2 input 0 is removed from regular cable arrays") {
		for (auto &core_cables : player.cables.samecore_cables) {
			for (auto &cable : core_cables) {
				for (size_t i = 0; i < cable.ins.size(); i++) {
					CHECK_FALSE((cable.ins[i] == Jack{2, 0}));
				}
			}
		}
		for (auto &core_cables : player.cables.diffcore_cables) {
			for (auto &cable : core_cables) {
				for (size_t i = 0; i < cable.ins.size(); i++) {
					CHECK_FALSE((cable.ins[i] == Jack{2, 0}));
				}
			}
		}
	}
}

TEST_CASE("Panel input to module input with no internal cable: direct routing (no summing needed)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: panel_direct
  module_slugs:
    0: PANEL_8
    1: MULTILFO
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Panel input routes directly to module (not through Hub)") {
		CHECK(player.get_panel_input_connection(0) == Jack{1, 0});
	}

	SUBCASE("No summed inputs or virtual cables needed") {
		for (auto &core_si : player.cables.summed_inputs) {
			CHECK(core_si.size() == 0);
		}
	}
}

TEST_CASE("Hub-to-Hub single passthrough: panel in 0 to panel out 0") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: hub_passthrough
  module_slugs:
    0: PANEL_8
  int_cables:
  mapped_ins:
    - panel_jack_id: 0
      ins:
        - module_id: 0
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Panel out 0 reads from Hub out 0 (panel in 0)") {
		CHECK(player.get_outconns()[0].size() == 1);
		CHECK(player.get_panel_output_connection(0, 0) == Jack{0, 0});
	}

	SUBCASE("Passthrough works: panel in value appears on panel out") {
		player.set_panel_input(0, 4.2f);
		float panel_out = player.get_panel_output(0);
		CHECK(panel_out == doctest::Approx(4.2f));
	}
}

TEST_CASE("Three internal cables to same input are summed") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: three_way_sum
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: LFOSINE
    3: LFOSINE
    4: MULTILFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 2
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
    - out:
        module_id: 3
        jack_id: 0
      ins:
        - module_id: 4
          jack_id: 0
  mapped_ins:
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Summed input for module 4 jack 0 has all three sources") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{4, 0}) {
					found = true;
					CHECK(si.outs.size() == 3);
				}
			}
		}
		CHECK(found);
	}
}

TEST_CASE("Summing part of a split: virt output splits to a virt input and panel output. The virt input also sums with "
		  "a panel input") {
	// Module 2 input 0 receives both an internal cable (from Module 1 output 0) and a panel input.
	// Module 1 output 0 is also mapped to panel out 0.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: mixed_sum
  module_slugs:
    0: PANEL_8
    1: LFOSINE
    2: MULTILFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
  mapped_ins:
    - panel_jack_id: 1
      ins:
        - module_id: 2
          jack_id: 0
  mapped_outs:
    - panel_jack_id: 0
      out:
        module_id: 1
        jack_id: 0
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 0
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Panel input 1 routes to Hub for summing") {
		CHECK(player.get_panel_input_connection(1) == Jack{0, 1});
	}

	SUBCASE("Summed input for module 2 jack 0 has LFO and Hub sources") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{2, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
					bool has_lfo = false, has_hub = false;
					for (size_t j = 0; j < si.outs.size(); j++) {
						if (si.outs[j] == Jack{1, 0})
							has_lfo = true;
						if (si.outs[j] == Jack{0, 1})
							has_hub = true;
					}
					CHECK(has_lfo);
					CHECK(has_hub);
				}
			}
		}
		CHECK(found);
	}

	SUBCASE("Panel output 0 reads from module 1") {
		CHECK(player.get_outconns()[0].size() == 1);
		CHECK(player.get_panel_output_connection(0) == Jack{1, 0});
	}
}

TEST_CASE("MIDI to Hub mapping") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: hub_midi_passthrough
  module_slugs:
    0: PANEL_8
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 1
  midi_poly_mode: 0
  midi_pitchwheel_range: 1
  mapped_lights: []
  vcvModuleStates: []
  suggested_samplerate: 0
  suggested_blocksize: 0
  bypassed_modules: []
  module_aliases: []
)"};
	// clang-format on

	MetaModule::PatchData pd;
	yaml_string_to_patch(patchyml, pd);

	MetaModule::PatchPlayer player;
	player.load_patch(pd);

	SUBCASE("Passthrough works: MIDI pitch appears on panel out") {
		player.set_midi_note_pitch(0, 4.2f, 0);
		float panel_out = player.get_panel_output(0);
		CHECK(panel_out == doctest::Approx(4.2f));
	}
}
