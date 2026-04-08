#include "doctest.h"
#include "patch-serial/patch_to_yaml.hh"
#include "patch-serial/yaml_to_patch.hh"

#include "patch_play/patch_player.hh"
#include "stubs/test_module.hh"
#include "stubs/test_poly_module.hh"
#include <fstream>
#include <string>

namespace
{
constexpr MetaModule::ModuleInfoView TestPanelInfo{.width_hp = 8};
constexpr MetaModule::ModuleInfoView TestModuleInfo{.width_hp = 8};
constexpr MetaModule::ModuleInfoView TestPolyModuleInfo{.width_hp = 8};

const std::array register_modules = {
	MetaModule::ModuleFactory::registerModuleType("HubMedium", TestPanel::create, TestPanelInfo, ""),
	MetaModule::ModuleFactory::registerModuleType("TestModule", TestModule::create, TestModuleInfo, ""),
	MetaModule::ModuleFactory::registerModuleType("TestPoly", TestPolyModule::create, TestPolyModuleInfo, ""),
};

auto *get_test_module(MetaModule::PatchPlayer &player, unsigned module_id) {
	return dynamic_cast<TestModule *>(player.modules[module_id].get());
}

auto *get_test_poly(MetaModule::PatchPlayer &player, unsigned module_id) {
	return dynamic_cast<TestPolyModule *>(player.modules[module_id].get());
}

} // namespace

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
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
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

	auto mono1 = get_test_module(player, 1);
	auto mono2 = get_test_module(player, 2);
	auto mono3 = get_test_module(player, 3);
	CHECK(mono1);
	CHECK(mono2);
	CHECK(mono3);

	mono1->set_input(0, 3.5f);
	CHECK(mono1->get_output(0) == 3.5f);

	mono2->set_input(0, 1.5f);
	CHECK(mono2->get_output(0) == 1.5f);

	player.update_patch();

	CHECK(mono3->get_output(0) == 5.f);

	SUBCASE("Cable cache has a summed input for module 3 jack 0 from both output jacks") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{3, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
					bool has_mod1 = false, has_mod2 = false;
					for (size_t j = 0; j < si.outs.size(); j++) {
						if (si.outs[j] == Jack{1, 0})
							has_mod1 = true;
						if (si.outs[j] == Jack{2, 0})
							has_mod2 = true;
					}
					CHECK(has_mod1);
					CHECK(has_mod2);
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
    0: HubMedium
    1: TestModule
    2: TestModule
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

	SUBCASE("Value propagates from module 1 to module 2 via cable") {
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		CHECK(mono1);
		CHECK(mono2);
		mono1->set_input(0, 2.5f);
		player.update_patch();
		CHECK(mono2->get_output(0) == doctest::Approx(2.5f));
	}
}

TEST_CASE("Summed panel output: two module outputs to same panel out jack") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: summed_panel_out
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
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
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		CHECK(mono1);
		CHECK(mono2);
		mono1->set_input(0, 3.0f);
		mono2->set_input(0, 2.0f);
		player.update_patch();
		CHECK(player.get_panel_output(0) == doctest::Approx(5.0f));
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
    0: HubMedium
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
    0: HubMedium
    1: TestModule
    2: TestModule
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

	SUBCASE("Module 2 jack 0 receives sum of panel input and cable source") {
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		CHECK(mono1);
		CHECK(mono2);
		// Panel in 0 contributes via Hub virtual cable; module 1 contributes via internal cable
		player.set_panel_input(0, 3.0f);
		mono1->set_input(0, 2.0f);
		player.update_patch();
		CHECK(mono2->get_output(0) == doctest::Approx(5.0f));
	}
}

TEST_CASE("Panel input to module input with no internal cable: direct routing (no summing needed)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: panel_direct
  module_slugs:
    0: HubMedium
    1: TestModule
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

	SUBCASE("Panel input value propagates to module jack") {
		auto mono1 = get_test_module(player, 1);
		CHECK(mono1);
		player.set_panel_input(0, 4.0f);
		player.update_patch();
		CHECK(mono1->get_output(0) == doctest::Approx(4.0f));
	}
}

TEST_CASE("Hub-to-Hub single passthrough: panel in 0 to panel out 0") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: hub_passthrough
  module_slugs:
    0: HubMedium
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
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
    4: TestModule
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

	SUBCASE("Module 4 jack 0 receives sum of all three cable sources") {
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		auto mono3 = get_test_module(player, 3);
		auto mono4 = get_test_module(player, 4);
		CHECK(mono1);
		CHECK(mono2);
		CHECK(mono3);
		CHECK(mono4);
		mono1->set_input(0, 1.0f);
		mono2->set_input(0, 2.0f);
		mono3->set_input(0, 3.0f);
		player.update_patch();
		CHECK(mono4->get_output(0) == doctest::Approx(6.0f));
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
    0: HubMedium
    1: TestModule
    2: TestModule
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

	SUBCASE("Summed input for module 2 jack 0 has module 1 and Hub sources") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{2, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
					bool has_mod1 = false, has_hub = false;
					for (size_t j = 0; j < si.outs.size(); j++) {
						if (si.outs[j] == Jack{1, 0})
							has_mod1 = true;
						if (si.outs[j] == Jack{0, 1})
							has_hub = true;
					}
					CHECK(has_mod1);
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

	SUBCASE("Panel out 0 reflects module 1 output") {
		auto mono1 = get_test_module(player, 1);
		CHECK(mono1);
		mono1->set_input(0, 4.0f);
		player.update_patch();
		CHECK(player.get_panel_output(0) == doctest::Approx(4.0f));
	}

	SUBCASE("Module 2 jack 0 receives sum of module 1 output and panel input 1") {
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		CHECK(mono1);
		CHECK(mono2);
		mono1->set_input(0, 2.0f);
		player.set_panel_input(1, 3.0f);
		player.update_patch();
		CHECK(mono2->get_output(0) == doctest::Approx(5.0f));
	}
}

// ============================================================================
// Poly cable tests
// ============================================================================

TEST_CASE("Poly cable: cable cache resolves poly buffers for TestPolyModule") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_resolve
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
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

	REQUIRE(get_test_poly(player, 1) != nullptr);
	REQUIRE(get_test_poly(player, 2) != nullptr);

	SUBCASE("Cable out_buf points to module 1 output poly buffer") {
		bool found = false;
		auto *mod1 = get_test_poly(player, 1);
		for (auto &core_cables : player.cables.samecore_cables) {
			for (auto &cable : core_cables) {
				if (cable.out == Jack{1, 0}) {
					found = true;
					CHECK(cable.out_buf.voltages == mod1->output_poly[0].data());
					CHECK(cable.out_buf.channels == &mod1->output_channels[0]);
				}
			}
		}
		if (!found) {
			for (auto &core_cables : player.cables.diffcore_cables) {
				for (auto &cable : core_cables) {
					if (cable.out == Jack{1, 0}) {
						found = true;
						CHECK(cable.out_buf.voltages == mod1->output_poly[0].data());
						CHECK(cable.out_buf.channels == &mod1->output_channels[0]);
					}
				}
			}
		}
		CHECK(found);
	}

	SUBCASE("Cable in_bufs points to module 2 input poly buffer") {
		bool found = false;
		auto *mod2 = get_test_poly(player, 2);
		auto check_cables = [&](auto &cable_list) {
			for (auto &core_cables : cable_list) {
				for (auto &cable : core_cables) {
					if (cable.out == Jack{1, 0}) {
						for (size_t i = 0; i < cable.ins.size(); i++) {
							if (cable.ins[i] == Jack{2, 0}) {
								found = true;
								CHECK(cable.in_bufs[i].voltages == mod2->input_poly[0].data());
								CHECK(cable.in_bufs[i].channels == &mod2->input_channels[0]);
							}
						}
					}
				}
			}
		};
		check_cables(player.cables.samecore_cables);
		check_cables(player.cables.diffcore_cables);
		CHECK(found);
	}
}

TEST_CASE("Poly cable: process_outputs copies poly channels from output to input") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_propagate
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);

	SUBCASE("All 4 poly channels are copied from output to input") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

		player.update_patch();

		CHECK(mod2->input_channels[0] == 4);
		CHECK(mod2->input_poly[0][0] == doctest::Approx(1.0f));
		CHECK(mod2->input_poly[0][1] == doctest::Approx(2.0f));
		CHECK(mod2->input_poly[0][2] == doctest::Approx(3.0f));
		CHECK(mod2->input_poly[0][3] == doctest::Approx(4.0f));
	}

	SUBCASE("Fewer than MaxPoly channels: only active channels copied") {
		mod1->output_channels[0] = 2;
		mod1->output_poly[0] = {5.0f, 6.0f, 99.0f, 99.0f};

		// Pre-fill destination with sentinel values
		mod2->input_poly[0] = {-1.f, -1.f, -1.f, -1.f};

		player.update_patch();

		CHECK(mod2->input_channels[0] == 2);
		CHECK(mod2->input_poly[0][0] == doctest::Approx(5.0f));
		CHECK(mod2->input_poly[0][1] == doctest::Approx(6.0f));
		// Channels beyond the active count are not guaranteed to be zeroed by process_outputs
	}

	SUBCASE("Single channel (mono-like poly)") {
		mod1->output_channels[0] = 1;
		mod1->output_poly[0] = {7.5f, 0.f, 0.f, 0.f};

		player.update_patch();

		CHECK(mod2->input_channels[0] == 1);
		CHECK(mod2->input_poly[0][0] == doctest::Approx(7.5f));
	}
}

TEST_CASE("Poly to mono cable: mono input receives first channel only") {
	// Module 1 (TestPoly) output 0 -> Module 2 (MultiLFO, mono) input 0
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_to_mono
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: MultiLFO
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

	auto *mod1 = get_test_poly(player, 1);
	REQUIRE(mod1 != nullptr);

	SUBCASE("Mono input receives only the first poly channel voltage") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {3.3f, 6.6f, 9.9f, 1.1f};

		player.update_patch();

		// MultiLFO is a regular CoreModule, so its input poly buffer is null.
		// process_outputs does poly->mono: set_input(jack_id, *out_buf.voltages)
		// which means only the first channel (3.3f) is used.
		// We can't easily read the mono module's input directly, but we can verify
		// the cable cache detected this as poly->mono:
		bool found = false;
		auto check = [&](auto &cable_list) {
			for (auto &core_cables : cable_list) {
				for (auto &cable : core_cables) {
					if (cable.out == Jack{1, 0}) {
						found = true;
						// Output is poly
						CHECK(cable.out_buf.voltages != nullptr);
						// Input is mono (nullptr)
						for (size_t i = 0; i < cable.ins.size(); i++) {
							if (cable.ins[i] == Jack{2, 0}) {
								CHECK(cable.in_bufs[i].voltages == nullptr);
							}
						}
					}
				}
			}
		};
		check(player.cables.samecore_cables);
		check(player.cables.diffcore_cables);
		CHECK(found);
	}
}

TEST_CASE("Mono to poly cable: poly input receives value in first channel") {
	// Module 1 (MultiLFO, mono output) -> Module 2 (TestPoly, poly input)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: mono_to_poly
  module_slugs:
    0: PANEL_8
    1: MultiLFO
    2: TestPoly
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

	auto *mod2 = get_test_poly(player, 2);
	REQUIRE(mod2 != nullptr);

	SUBCASE("Cable cache: output is mono, input is poly") {
		bool found = false;
		auto check = [&](auto &cable_list) {
			for (auto &core_cables : cable_list) {
				for (auto &cable : core_cables) {
					if (cable.out == Jack{1, 0}) {
						found = true;
						CHECK(cable.out_buf.voltages == nullptr);
					}
				}
			}
		};
		check(player.cables.samecore_cables);
		check(player.cables.diffcore_cables);
		CHECK(found);
	}

	SUBCASE("Mono output value is set via set_input on poly module") {
		// When out_buf.voltages is null (mono output), process_outputs uses get_output/set_input.
		// The TestPolyModule::set_input stores in inputs_mono, not input_poly.
		// This is the mono->poly path where the mono value arrives via set_input().
		player.update_patch();

		float lfo_out = player.modules[1]->get_output(0);
		CHECK(mod2->inputs_mono[0] == doctest::Approx(lfo_out));
	}
}

TEST_CASE("Poly output mapped to panel: get_panel_output sums all poly channels") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_panel_sum
  module_slugs:
    0: PANEL_8
    1: TestPoly
  int_cables:
  mapped_ins:
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

	auto *mod1 = get_test_poly(player, 1);
	REQUIRE(mod1 != nullptr);

	SUBCASE("out_conns has poly buffer pointer for panel jack 0") {
		auto &conns = player.get_outconns()[0];
		REQUIRE(conns.size() == 1);
		CHECK(conns[0].buf.voltages == mod1->output_poly[0].data());
		CHECK(conns[0].buf.channels == &mod1->output_channels[0]);
	}

	SUBCASE("get_panel_output sums all 4 poly channels") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

		float panel_out = player.get_panel_output(0);
		CHECK(panel_out == doctest::Approx(10.0f));
	}

	SUBCASE("get_panel_output sums only active channels") {
		mod1->output_channels[0] = 2;
		mod1->output_poly[0] = {5.0f, 7.0f, 99.0f, 99.0f};

		float panel_out = player.get_panel_output(0);
		CHECK(panel_out == doctest::Approx(12.0f)); // 5 + 7
	}

	SUBCASE("Single-channel poly output gives just that value") {
		mod1->output_channels[0] = 1;
		mod1->output_poly[0] = {3.14f, 0.f, 0.f, 0.f};

		float panel_out = player.get_panel_output(0);
		CHECK(panel_out == doctest::Approx(3.14f));
	}
}

TEST_CASE("Two poly outputs summed to same panel jack") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_sum_panel
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);

	SUBCASE("Panel out 0 has two poly connections") {
		auto &conns = player.get_outconns()[0];
		CHECK(conns.size() == 2);
	}

	SUBCASE("get_panel_output sums all channels from both modules") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

		mod2->output_channels[0] = 3;
		mod2->output_poly[0] = {10.0f, 20.0f, 30.0f, 0.0f};

		float panel_out = player.get_panel_output(0);
		// (1+2+3+4) + (10+20+30) = 10 + 60 = 70
		CHECK(panel_out == doctest::Approx(70.0f));
	}

	SUBCASE("Mixed: one poly + one zero-channel output") {
		mod1->output_channels[0] = 2;
		mod1->output_poly[0] = {5.0f, 5.0f, 0.0f, 0.0f};

		mod2->output_channels[0] = 0;
		mod2->output_poly[0] = {99.0f, 99.0f, 0.0f, 0.0f};

		float panel_out = player.get_panel_output(0);
		// Only mod1's 2 channels contribute: 5 + 5 = 10
		CHECK(panel_out == doctest::Approx(10.0f));
	}
}

TEST_CASE("Poly cable: one output splits to two poly inputs") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_split
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
    3: TestPoly
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	auto *mod3 = get_test_poly(player, 3);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);
	REQUIRE(mod3 != nullptr);

	SUBCASE("Both inputs receive all poly channels") {
		mod1->output_channels[0] = 3;
		mod1->output_poly[0] = {1.5f, 2.5f, 3.5f, 0.0f};

		player.update_patch();

		CHECK(mod2->input_channels[0] == 3);
		CHECK(mod2->input_poly[0][0] == doctest::Approx(1.5f));
		CHECK(mod2->input_poly[0][1] == doctest::Approx(2.5f));
		CHECK(mod2->input_poly[0][2] == doctest::Approx(3.5f));

		CHECK(mod3->input_channels[0] == 3);
		CHECK(mod3->input_poly[0][0] == doctest::Approx(1.5f));
		CHECK(mod3->input_poly[0][1] == doctest::Approx(2.5f));
		CHECK(mod3->input_poly[0][2] == doctest::Approx(3.5f));
	}
}

TEST_CASE("Poly cable: split to poly and mono input simultaneously") {
	// Module 1 (poly output) -> Module 2 (poly input) and Module 3 (mono input)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_split_mixed
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
    3: MultiLFO
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);

	SUBCASE("Poly input gets all channels, mono input gets first channel") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {10.0f, 20.0f, 30.0f, 40.0f};

		player.update_patch();

		// Poly input (module 2) gets all channels
		CHECK(mod2->input_channels[0] == 4);
		CHECK(mod2->input_poly[0][0] == doctest::Approx(10.0f));
		CHECK(mod2->input_poly[0][1] == doctest::Approx(20.0f));
		CHECK(mod2->input_poly[0][2] == doctest::Approx(30.0f));
		CHECK(mod2->input_poly[0][3] == doctest::Approx(40.0f));

		// Mono input (module 3): verify cable cache has null in_buf for it
		bool found_mono = false;
		auto check = [&](auto &cable_list) {
			for (auto &core_cables : cable_list) {
				for (auto &cable : core_cables) {
					if (cable.out == Jack{1, 0}) {
						for (size_t i = 0; i < cable.ins.size(); i++) {
							if (cable.ins[i] == Jack{3, 0}) {
								found_mono = true;
								CHECK(cable.in_bufs[i].voltages == nullptr);
							}
						}
					}
				}
			}
		};
		check(player.cables.samecore_cables);
		check(player.cables.diffcore_cables);
		CHECK(found_mono);
	}
}

TEST_CASE("Poly cable: second output jack also works") {
	// Uses output jack 1 (the second output) to verify jack_id indexing
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_jack1
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
  int_cables:
    - out:
        module_id: 1
        jack_id: 1
      ins:
        - module_id: 2
          jack_id: 1
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);

	SUBCASE("Output jack 1 poly data propagates to input jack 1") {
		mod1->output_channels[1] = 3;
		mod1->output_poly[1] = {100.0f, 200.0f, 300.0f, 0.0f};

		player.update_patch();

		CHECK(mod2->input_channels[1] == 3);
		CHECK(mod2->input_poly[1][0] == doctest::Approx(100.0f));
		CHECK(mod2->input_poly[1][1] == doctest::Approx(200.0f));
		CHECK(mod2->input_poly[1][2] == doctest::Approx(300.0f));
	}

	SUBCASE("Cable cache resolves correct jack") {
		bool found = false;
		auto check = [&](auto &cable_list) {
			for (auto &core_cables : cable_list) {
				for (auto &cable : core_cables) {
					if (cable.out == Jack{1, 1}) {
						found = true;
						CHECK(cable.out_buf.voltages == mod1->output_poly[1].data());
						CHECK(cable.out_buf.channels == &mod1->output_channels[1]);
					}
				}
			}
		};
		check(player.cables.samecore_cables);
		check(player.cables.diffcore_cables);
		CHECK(found);
	}
}

TEST_CASE("Poly output to panel: second output jack summed to panel") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_panel_jack1
  module_slugs:
    0: PANEL_8
    1: TestPoly
  int_cables:
  mapped_ins:
  mapped_outs:
    - panel_jack_id: 1
      out:
        module_id: 1
        jack_id: 1
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

	auto *mod1 = get_test_poly(player, 1);
	REQUIRE(mod1 != nullptr);

	SUBCASE("Panel output 1 sums poly channels from output jack 1") {
		mod1->output_channels[1] = 4;
		mod1->output_poly[1] = {0.1f, 0.2f, 0.3f, 0.4f};

		float panel_out = player.get_panel_output(1);
		CHECK(panel_out == doctest::Approx(1.0f));
	}
}

TEST_CASE("Poly cable with panel input summing: panel + poly cable to same input") {
	// Panel input 0 is mapped to TestPoly (module 2) input 0.
	// Module 1 output 0 also has a cable to module 2 input 0.
	// This creates a summed input via the Hub routing mechanism.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_panel_sum_cable
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
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

	SUBCASE("Panel input 0 routes to Hub for summing") {
		CHECK(player.get_panel_input_connection(0) == Jack{0, 0});
	}

	SUBCASE("Summed input exists for module 2 jack 0") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{2, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
				}
			}
		}
		CHECK(found);
	}
}

TEST_CASE("Poly summed inputs: two poly outputs with different channel counts to one poly input") {
	// Module 1 output 0 (4 channels) and Module 2 output 0 (2 channels)
	// both cable to Module 3 input 0 (poly). Result: 4 channels, per-channel sum.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_summed
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
    3: TestPoly
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	auto *mod3 = get_test_poly(player, 3);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);
	REQUIRE(mod3 != nullptr);

	SUBCASE("Summed input entry exists with poly buffers resolved") {
		bool found = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{3, 0}) {
					found = true;
					CHECK(si.outs.size() == 2);
					// Input poly buffer resolved
					CHECK(si.in_buf.voltages == mod3->input_poly[0].data());
					CHECK(si.in_buf.channels == &mod3->input_channels[0]);
					// Output poly buffers resolved
					for (size_t i = 0; i < si.outs.size(); i++) {
						CHECK(si.out_bufs[i].voltages != nullptr);
						CHECK(si.out_bufs[i].channels != nullptr);
					}
				}
			}
		}
		CHECK(found);
	}

	SUBCASE("Input channel count is max of source channel counts") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

		mod2->output_channels[0] = 2;
		mod2->output_poly[0] = {10.0f, 20.0f, 0.0f, 0.0f};

		player.update_patch();

		CHECK(mod3->input_channels[0] == 4);
	}

	SUBCASE("Per-channel summing with different channel counts") {
		mod1->output_channels[0] = 4;
		mod1->output_poly[0] = {1.0f, 2.0f, 3.0f, 4.0f};

		mod2->output_channels[0] = 2;
		mod2->output_poly[0] = {10.0f, 20.0f, 0.0f, 0.0f};

		player.update_patch();

		// ch0: 1 + 10 = 11, ch1: 2 + 20 = 22, ch2: 3 + 0 = 3, ch3: 4 + 0 = 4
		CHECK(mod3->input_poly[0][0] == doctest::Approx(11.0f));
		CHECK(mod3->input_poly[0][1] == doctest::Approx(22.0f));
		CHECK(mod3->input_poly[0][2] == doctest::Approx(3.0f));
		CHECK(mod3->input_poly[0][3] == doctest::Approx(4.0f));
	}

	SUBCASE("Both sources same channel count") {
		mod1->output_channels[0] = 3;
		mod1->output_poly[0] = {1.0f, 1.0f, 1.0f, 0.0f};

		mod2->output_channels[0] = 3;
		mod2->output_poly[0] = {2.0f, 3.0f, 4.0f, 0.0f};

		player.update_patch();

		CHECK(mod3->input_channels[0] == 3);
		CHECK(mod3->input_poly[0][0] == doctest::Approx(3.0f));
		CHECK(mod3->input_poly[0][1] == doctest::Approx(4.0f));
		CHECK(mod3->input_poly[0][2] == doctest::Approx(5.0f));
	}

	SUBCASE("Single-channel sources sum to single channel") {
		mod1->output_channels[0] = 1;
		mod1->output_poly[0] = {5.0f, 0.0f, 0.0f, 0.0f};

		mod2->output_channels[0] = 1;
		mod2->output_poly[0] = {7.0f, 0.0f, 0.0f, 0.0f};

		player.update_patch();

		CHECK(mod3->input_channels[0] == 1);
		CHECK(mod3->input_poly[0][0] == doctest::Approx(12.0f));
	}
}

TEST_CASE("Poly summed inputs: three poly sources with varied channel counts") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_sum_3way
  module_slugs:
    0: PANEL_8
    1: TestPoly
    2: TestPoly
    3: TestPoly
    4: TestPoly
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

	auto *mod1 = get_test_poly(player, 1);
	auto *mod2 = get_test_poly(player, 2);
	auto *mod3 = get_test_poly(player, 3);
	auto *mod4 = get_test_poly(player, 4);
	REQUIRE(mod1 != nullptr);
	REQUIRE(mod2 != nullptr);
	REQUIRE(mod3 != nullptr);
	REQUIRE(mod4 != nullptr);

	SUBCASE("Three sources: 1ch, 3ch, 4ch -> 4ch output with per-channel sums") {
		mod1->output_channels[0] = 1;
		mod1->output_poly[0] = {100.0f, 0.0f, 0.0f, 0.0f};

		mod2->output_channels[0] = 3;
		mod2->output_poly[0] = {1.0f, 2.0f, 3.0f, 0.0f};

		mod3->output_channels[0] = 4;
		mod3->output_poly[0] = {0.1f, 0.2f, 0.3f, 0.4f};

		player.update_patch();

		CHECK(mod4->input_channels[0] == 4);
		CHECK(mod4->input_poly[0][0] == doctest::Approx(101.1f));
		CHECK(mod4->input_poly[0][1] == doctest::Approx(2.2f));
		CHECK(mod4->input_poly[0][2] == doctest::Approx(3.3f));
		CHECK(mod4->input_poly[0][3] == doctest::Approx(0.4f));
	}
}

TEST_CASE("Poly summed inputs: mono + poly sources summed to poly input") {
	// Module 1 (MultiLFO, mono output) and Module 2 (TestPoly, poly output)
	// both cable to Module 3 (TestPoly, poly input). Mono adds to channel 0.
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: poly_sum_mixed
  module_slugs:
    0: PANEL_8
    1: MultiLFO
    2: TestPoly
    3: TestPoly
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

	auto *mod2 = get_test_poly(player, 2);
	auto *mod3 = get_test_poly(player, 3);
	REQUIRE(mod2 != nullptr);
	REQUIRE(mod3 != nullptr);

	SUBCASE("Mono source adds to channel 0, poly source adds per-channel") {
		mod2->output_channels[0] = 3;
		mod2->output_poly[0] = {10.0f, 20.0f, 30.0f, 0.0f};

		player.update_patch();

		float mono_val = player.modules[1]->get_output(0);

		// Channel count comes from the poly source (3)
		CHECK(mod3->input_channels[0] == 3);
		// ch0 = mono_val + 10, ch1 = 20, ch2 = 30
		CHECK(mod3->input_poly[0][0] == doctest::Approx(mono_val + 10.0f));
		CHECK(mod3->input_poly[0][1] == doctest::Approx(20.0f));
		CHECK(mod3->input_poly[0][2] == doctest::Approx(30.0f));
	}
}

// ============================================================================
// MIDI Poly Cable Tests
// ============================================================================

TEST_CASE("MIDI poly cable: MidiNotePolyJack writes to poly buffer") {
	// Map MidiNotePolyJack to TestPoly module input 0
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_poly_note
  module_slugs:
    0: PANEL_8
    1: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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

	auto *mod = get_test_poly(player, 1);
	REQUIRE(mod != nullptr);

	// Simulate MIDI connected
	player.set_midi_connected();

	SUBCASE("Write pitch to poly channel 0") {
		player.set_midi_note_pitch(0, 1.5f, 0);
		CHECK(mod->input_poly[0][0] == doctest::Approx(1.5f));
	}

	SUBCASE("Write pitch to poly channel 3") {
		player.set_midi_note_pitch(3, -2.0f, 0);
		CHECK(mod->input_poly[0][3] == doctest::Approx(-2.0f));
	}

	SUBCASE("poly_chan >= MaxPolyChannels is no-op") {
		mod->input_poly[0] = {};
		player.set_midi_note_pitch(4, 5.0f, 0);
		// All channels remain zero
		for (unsigned ch = 0; ch < CoreProcessor::MaxPolyChannels; ch++)
			CHECK(mod->input_poly[0][ch] == doctest::Approx(0.0f));
	}
}

TEST_CASE("MIDI poly cable: gate and velocity poly") {
	// Map MidiGatePolyJack and MidiVelPolyJack to TestPoly inputs 0 and 1
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_poly_gate_vel
  module_slugs:
    0: PANEL_8
    1: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 337
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 338
      ins:
        - module_id: 1
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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

	auto *mod = get_test_poly(player, 1);
	REQUIRE(mod != nullptr);

	player.set_midi_connected();

	SUBCASE("Gate poly writes to channel") {
		player.set_midi_note_gate(1, 10.f, 0);
		CHECK(mod->input_poly[0][1] == doctest::Approx(10.f));
	}

	SUBCASE("Velocity poly writes to channel") {
		player.set_midi_note_velocity(2, 63, 0);
		CHECK(mod->input_poly[1][2] == doctest::Approx(63.f / 12.7f));
	}
}

TEST_CASE("MIDI poly cable: MIDI channel filtering") {
	// Map MidiNotePolyJack with MIDI channel 3 (panel_jack_id = 0x150 | 0x800 | (2 << 12) = 0x2950)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_poly_chan_filter
  module_slugs:
    0: PANEL_8
    1: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 10576
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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

	auto *mod = get_test_poly(player, 1);
	REQUIRE(mod != nullptr);

	player.set_midi_connected();

	SUBCASE("Matching MIDI channel passes through") {
		// midi_chan=2 means MIDI channel 3 (0-indexed in event)
		player.set_midi_note_pitch(0, 3.0f, 2);
		CHECK(mod->input_poly[0][0] == doctest::Approx(3.0f));
	}

	SUBCASE("Non-matching MIDI channel is filtered") {
		mod->input_poly[0] = {};
		player.set_midi_note_pitch(0, 3.0f, 5); // channel 6 != channel 3
		CHECK(mod->input_poly[0][0] == doctest::Approx(0.0f));
	}
}

TEST_CASE("MIDI poly cable: channel count is set correctly") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_poly_chancount
  module_slugs:
    0: PANEL_8
    1: TestPoly
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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

	auto *mod = get_test_poly(player, 1);
	REQUIRE(mod != nullptr);

	player.set_midi_connected();

	SUBCASE("Channel count set to MaxPolyChannels on connect") {
		CHECK(mod->input_channels[0] == CoreProcessor::MaxPolyChannels);
	}

	SUBCASE("set_midi_poly_num updates channel count") {
		player.set_midi_poly_num(2);
		CHECK(mod->input_channels[0] == 2);
	}
}

TEST_CASE("MIDI poly cable into a mono module falls back to set_input with channel 0 and ignores channels > 0") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_poly_fallback
  module_slugs:
    0: PANEL_8
    1: TestMono
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 1
          jack_id: 0
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	SUBCASE("Channel 0 falls back to set_input and Channel >= 1 with null buffer is no-op") {
		player.set_midi_note_pitch(0, 2.5f, 0);
		player.set_midi_note_pitch(1, 3.5f, 0);
		player.set_midi_note_pitch(2, 4.5f, 0);
		player.set_midi_note_pitch(3, 5.5f, 0);

		CHECK(player.modules[1]->get_output(0) == 2.5f);
		CHECK(player.modules[1]->get_output(1) == 0.f);
		CHECK(player.modules[1]->get_output(2) == 0.f);
		CHECK(player.modules[1]->get_output(3) == 0.f);

		auto *module = get_test_module(player, 1);
		CHECK(module->outs[0] == 2.5f);
		CHECK(module->outs[1] == 0.f);
		CHECK(module->outs[2] == 0.f);
		CHECK(module->outs[3] == 0.f);
	}
}

TEST_CASE("MIDI poly cable patched to Panel Out jack") {
	// Map MidiNotePolyJack and MidiGatePolyJack to Panel Out 1 and Panel Out 2
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_poly_gate_vel
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 336
      ins:
        - module_id: 0
          jack_id: 0
    - panel_jack_id: 337
      ins:
        - module_id: 0
          jack_id: 1
  mapped_outs:
  static_knobs:
  mapped_knobs:
  midi_maps:
  midi_poly_num: 4
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
	player.set_midi_connected();

	SUBCASE("Note poly channel 0 writes to panel out 1, but other poly channels do not") {
		player.set_midi_note_pitch(0, 1.f, 0);
		CHECK(player.get_panel_output(0) == 1.f);

		// poly channel 1: output does not change
		player.set_midi_note_pitch(1, 3.f, 0);
		CHECK(player.get_panel_output(0) == 1.f);

		// poly channel 2: output does not change
		player.set_midi_note_pitch(2, 2.f, 0);
		CHECK(player.get_panel_output(0) == 1.f);

		// Poly channel 0: output changes
		player.set_midi_note_pitch(0, 2.f, 0);
		CHECK(player.get_panel_output(0) == 2.f);
	}

	SUBCASE("Gate poly writes to panel out 2") {
		player.set_midi_note_gate(0, 1.f, 0);
		CHECK(player.get_panel_output(1) == doctest::Approx(1.f));

		player.set_midi_note_gate(1, 99.f, 0); // ch1: no effect
		CHECK(player.get_panel_output(1) == doctest::Approx(1.f));

		player.set_midi_note_gate(0, 2.f, 0);
		CHECK(player.get_panel_output(1) == doctest::Approx(2.f));
	}
}

TEST_CASE("MIDI to Hub mapping") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: hub_midi_passthrough
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 1
    - panel_jack_id: 0x110
      ins:
        - module_id: 0
          jack_id: 4 
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

	player.set_midi_note_pitch(0, 4.2f, 0);
	float panel_out = player.get_panel_output(1);
	CHECK(panel_out == doctest::Approx(4.2f));

	player.set_midi_note_gate(0, 8.f, 0);
	panel_out = player.get_panel_output(4);
	CHECK(panel_out == doctest::Approx(8.f));
}

TEST_CASE("MIDI to Hub summed with Hub to Hub mapping") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: hub_midi_passthrough
  module_slugs:
    0: HubMedium
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 0
          jack_id: 2 
    - panel_jack_id: 1
      ins:
        - module_id: 0
          jack_id: 2 
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
	// printf("load\n");
	player.load_patch(pd);

	SUBCASE("Set just MIDI") {
		player.set_midi_note_pitch(0, 7.f, 0);
		float panel_out = player.get_panel_output(2);
		CHECK(panel_out == doctest::Approx(7.f));
	}
	SUBCASE("Set just Panel In") {
		player.set_panel_input(1, 3.f);
		float panel_out = player.get_panel_output(2);
		CHECK(panel_out == doctest::Approx(3.f));
	}
	SUBCASE("Set MIDI and Panel In") {
		player.set_panel_input(1, 3.f);
		player.set_midi_note_pitch(0, 7.f, 0);
		float panel_out = player.get_panel_output(2);
		CHECK(panel_out == doctest::Approx(10.f));
	}
	SUBCASE("Set a different Panel In that matches panel out ID") {
		// printf("set_panel_input(2, 6.f)\n");
		player.set_panel_input(2, 6.f);
		float panel_out = player.get_panel_output(2);
		CHECK(panel_out == doctest::Approx(0.f));

		// printf("done\n");
	}
}

TEST_CASE("Split: one output fans to multiple inputs — all destinations receive same value") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
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

	SUBCASE("No summed inputs — split destinations are independent") {
		for (auto &core_si : player.cables.summed_inputs) {
			CHECK(core_si.size() == 0);
		}
	}

	SUBCASE("Both destinations receive the same value from the source") {
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		auto mono3 = get_test_module(player, 3);
		CHECK(mono1);
		CHECK(mono2);
		CHECK(mono3);
		mono1->set_input(0, 2.5f);
		player.update_patch();
		CHECK(mono2->get_output(0) == doctest::Approx(2.5f));
		CHECK(mono3->get_output(0) == doctest::Approx(2.5f));
	}
}

TEST_CASE("MIDI to module input directly (not via Hub)") {
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: midi_direct
  module_slugs:
    0: HubMedium
    1: TestModule
  int_cables:
  mapped_ins:
    - panel_jack_id: 256
      ins:
        - module_id: 1
          jack_id: 0
    - panel_jack_id: 0x110
      ins:
        - module_id: 1
          jack_id: 1
    - panel_jack_id: 0x200
      ins:
        - module_id: 1
          jack_id: 2
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

	auto mono1 = get_test_module(player, 1);
	CHECK(mono1);

	SUBCASE("MIDI note pitch routes directly to module jack 0") {
		player.set_midi_note_pitch(0, 4.5f, 0);
		CHECK(mono1->get_output(0) == doctest::Approx(4.5f));
	}

	SUBCASE("MIDI note gate routes directly to module jack 1") {
		player.set_midi_note_gate(0, 8.f, 0);
		CHECK(mono1->get_output(1) == doctest::Approx(8.f));
	}

	SUBCASE("MIDI CC 0 routes directly to module jack 2, scaled to 0-10V") {
		player.set_midi_cc(0, 127, 0);
		CHECK(mono1->get_output(2) == doctest::Approx(127.f / 12.7f));
	}
}

TEST_CASE("Split combined with sum: source fans to two destinations, second source sums at one") {
	// Module 1 output 0 splits to module 2 jack 0 and module 3 jack 0.
	// Module 4 output 0 also connects to module 2 jack 0, so module 2 has a summed input.
	// Module 3 receives only the split (no sum).
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: split_plus_sum
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
    3: TestModule
    4: TestModule
  int_cables:
    - out:
        module_id: 1
        jack_id: 0
      ins:
        - module_id: 2
          jack_id: 0
        - module_id: 3
          jack_id: 0
    - out:
        module_id: 4
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

	SUBCASE("Module 2 jack 0 is summed; module 3 jack 0 is a plain cable") {
		bool found_sum = false;
		for (auto &core_si : player.cables.summed_inputs) {
			for (auto &si : core_si) {
				if (si.in == Jack{2, 0}) {
					found_sum = true;
					CHECK(si.outs.size() == 2);
				}
				CHECK_FALSE(si.in == Jack{3, 0});
			}
		}
		CHECK(found_sum);
	}

	SUBCASE("Module 2 receives sum; module 3 receives only module 1 value") {
		auto mono1 = get_test_module(player, 1);
		auto mono2 = get_test_module(player, 2);
		auto mono3 = get_test_module(player, 3);
		auto mono4 = get_test_module(player, 4);
		CHECK(mono1);
		CHECK(mono2);
		CHECK(mono3);
		CHECK(mono4);
		mono1->set_input(0, 3.0f);
		mono4->set_input(0, 1.5f);
		player.update_patch();
		CHECK(mono2->get_output(0) == doctest::Approx(4.5f));
		CHECK(mono3->get_output(0) == doctest::Approx(3.0f));
	}
}

TEST_CASE("Full round-trip: panel in routes to module, module output cables to second module, mapped to panel out") {
	// panel_in 0 → module 1 jack 0 (direct) → module 2 jack 0 (cable) → panel_out 0 (mapped_outs)
	// clang-format off
	std::string patchyml{R"(
PatchData:
  patch_name: round_trip
  module_slugs:
    0: HubMedium
    1: TestModule
    2: TestModule
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
        - module_id: 1
          jack_id: 0
  mapped_outs:
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

	SUBCASE("Panel in value flows through both modules and appears on panel out") {
		player.set_panel_input(0, 3.3f);
		player.update_patch();
		CHECK(player.get_panel_output(0) == doctest::Approx(3.3f));
	}

	SUBCASE("Changing panel in changes panel out after update") {
		player.set_panel_input(0, 1.0f);
		player.update_patch();
		CHECK(player.get_panel_output(0) == doctest::Approx(1.0f));

		player.set_panel_input(0, 5.0f);
		player.update_patch();
		CHECK(player.get_panel_output(0) == doctest::Approx(5.0f));
	}
}
