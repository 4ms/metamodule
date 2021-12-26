#include "doctest.h"
#include "patch_player.hh"

// The test data in these unit tests was generated using VCV rack to create a .mmpatch binary file.
// This file is then converted to a raw C-array using:
// xxd -i -c 8 patchfile.mmpatch > patchfile.hh
// When generating a .mmpatch file, there's also a human-readable .txt file (actually is in YAML format)
// The .txt file is useful for verifying the expected values

#include "patches/unittest_patchheader.hh"

TEST_CASE("Header loads ok") {
	static const PatchHeader expected_header = {
		.header_version = 1,
		.patch_name = "unittest_patchheader",
		.num_modules = 6,
		.num_int_cables = 2,
		.num_mapped_ins = 7,
		.num_mapped_outs = 5,
		.num_static_knobs = 23,
		.num_mapped_knobs = 8,
	};

	auto *ph = reinterpret_cast<PatchHeader *>(unittest_patchheader_mmpatch);
	CHECK(expected_header.header_version == ph->header_version);
	CHECK(expected_header.patch_name == ph->patch_name);
	CHECK(expected_header.num_modules == ph->num_modules);
	CHECK(expected_header.num_int_cables == ph->num_int_cables);
	CHECK(expected_header.num_mapped_ins == ph->num_mapped_ins);
	CHECK(expected_header.num_mapped_outs == ph->num_mapped_outs);
	CHECK(expected_header.num_static_knobs == ph->num_static_knobs);
	CHECK(expected_header.num_mapped_knobs == ph->num_mapped_knobs);
}

TEST_CASE("Module list loads ok") {
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_patchheader_mmpatch);
	REQUIRE(ph->num_modules == 6);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	CHECK(strcmp(player.module_slugs[0].data(), "PANEL_8") == 0);
	CHECK(strcmp(player.module_slugs[1].data(), "LFOSINE") == 0);
	CHECK(strcmp(player.module_slugs[2].data(), "MULTILFO") == 0);
	CHECK(strcmp(player.module_slugs[3].data(), "REVERB") == 0);
	CHECK(strcmp(player.module_slugs[4].data(), "KARPLUS") == 0);
	CHECK(strcmp(player.module_slugs[5].data(), "COMPLEXENVELOPE") == 0);
}

#include "patches/unittest_outmap.hh"
TEST_CASE("Simple output jack mapping") {
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_mmpatch);
	REQUIRE(ph->num_mapped_outs == 3);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

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

#include "patches/unittest_outmap_overlapping_cable.hh"
TEST_CASE("Internal cables: single and stacked") {
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_overlapping_cable_mmpatch);

	// In VCV Rack, if two cables are stacked, they appear as two separate cables.
	// Contrary to this, we consider them as a single cable, with one output and two inputs.
	// So, this patch should have 2 cables (a 1->1 and a 1->2)
	CHECK(ph->num_int_cables == 2);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);

	bool found_cable1 = false;
	bool found_cable2 = false;
	int cable1_idx = -1;
	int cable2_idx = -1;

	Jack end_of_cable = Jack{-1, -1};

	for (int net_i = 0; net_i < ph->num_int_cables; net_i++) {
		auto &cable = player.int_cables[net_i];

		// Check for cable1: 1->1 cable
		// {1,3} -> {2,0}
		if (cable.out == Jack{1, 3}) {
			if (cable.ins[0] == Jack{2, 0}) {
				if (cable.ins[1] == end_of_cable) {
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
				if (cable.ins[2] == end_of_cable) {
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
			CHECK(player.num_int_cable_ins[cable1_idx] == 1);
			CHECK(player.num_int_cable_ins[cable2_idx] == 2);
		}
	}
}

TEST_CASE("It's OK to have a Panel output jack mapping to an virtual input jack that has a valid cable") {
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_overlapping_cable_mmpatch);

	CHECK(ph->num_mapped_outs == 3);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

	SUBCASE("Check if output connection data is correct") {
		CHECK(player.get_panel_output_connection(0) == Jack{1, 3});
		CHECK(player.get_panel_output_connection(1) == Jack{1, 1});
		CHECK(player.get_panel_output_connection(2) == Jack{2, 1});

		SUBCASE("Unmapped jack is connected to 0,0") {
			CHECK(player.get_panel_output_connection(3) == Jack{0, 0});
			CHECK(player.get_panel_output_connection(4) == Jack{0, 0});
		}
	}
}

#include "patches/unittest_inmapping.hh"
// Note: we do not support multiple input mappings in VCV (yet), so aren't testing for it now
// because there's no easy way to create the test data
TEST_CASE("Simple input jack mapping") {
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_inmapping_mmpatch);
	REQUIRE(ph->num_mapped_ins == 6);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

	SUBCASE("Check if input connection data is correct") {
		CHECK(player.get_panel_input_connection(0) == Jack{1, 0});
		CHECK(player.get_panel_input_connection(1) == Jack{1, 2});
		CHECK(player.get_panel_input_connection(2) == Jack{2, 1});
		CHECK(player.get_panel_input_connection(3) == Jack{2, 0});
		CHECK(player.get_panel_input_connection(7) == Jack{1, 1});
		CHECK(player.get_panel_input_connection(8) == Jack{1, 3});

		SUBCASE("Unmapped jacks are connected to 0,0") {
			CHECK(player.get_panel_input_connection(4) == Jack{0, 0});
			CHECK(player.get_panel_input_connection(5) == Jack{0, 0});
			CHECK(player.get_panel_input_connection(6) == Jack{0, 0});

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
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_inmapping_overlapping_mmpatch);
	REQUIRE(ph->num_mapped_ins == 1);
	REQUIRE(ph->num_int_cables == 1);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

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
			CHECK(player.int_cables[0].out == Jack{2, 0});
			CHECK(player.num_int_cable_ins[0] == 1);
			CHECK(player.int_cables[0].ins[0] == Jack{1, 0});
		}
	}
}

#include "patches/unittest_dup_mod_index.hh"
TEST_CASE("Dup module index") {
	SUBCASE("If there's more than one of a module type, get the correct 'dup index' for each") {
		auto *ph = reinterpret_cast<PatchHeader *>(unittest_dup_mod_index_mmpatch);
		REQUIRE(ph->num_modules == 8);

		MetaModule::PatchPlayer player;
		player.load_patch_from_header(ph);
		player.calc_multiple_module_indicies();

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
