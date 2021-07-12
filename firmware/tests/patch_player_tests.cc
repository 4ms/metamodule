#include "doctest.h"
#include "patch_player.hh"
#include <iostream>

// The test data in these unit tests was generated using VCV rack to create a .mmpatch binary file.
// This file is then converted to a raw C-array using:
// xxd -i -c 8 patchfile.mmpatch > patchfile.hh
// When generating a .mmpatch file, there's also a human-readable .txt file (actually is in YAML format)
// The .txt file is useful for verifying the expected values

#include "patches/unittest_patchheader.hh"

TEST_CASE("Header loads ok")
{
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

TEST_CASE("Module list loads ok")
{
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_patchheader_mmpatch);
	REQUIRE(ph->num_modules == 6);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	CHECK(strcmp(player.module_slugs[0].cstr(), "PANEL_8") == 0);
	CHECK(strcmp(player.module_slugs[1].cstr(), "LFOSINE") == 0);
	CHECK(strcmp(player.module_slugs[2].cstr(), "MULTILFO") == 0);
	CHECK(strcmp(player.module_slugs[3].cstr(), "REVERB") == 0);
	CHECK(strcmp(player.module_slugs[4].cstr(), "KARPLUS") == 0);
	CHECK(strcmp(player.module_slugs[5].cstr(), "COMPLEXENVELOPE") == 0);
}

#include "patches/unittest_outmap.hh"
TEST_CASE("Simple output jack mapping")
{
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_mmpatch);
	REQUIRE(ph->num_mapped_outs == 3);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

	SUBCASE("Check if mapped_outs[] data was loaded OK")
	{
		// These tests are commented out because it doesn't matter if they're true or not,
		// as long as the output connection data tests pass
		// But they can be useful in debugging
		// CHECK(player.mapped_outs[0].panel_jack_id == 1);
		// CHECK(player.mapped_outs[0].out.module_id == 1);
		// CHECK(player.mapped_outs[0].out.jack_id == 1);

		// CHECK(player.mapped_outs[1].panel_jack_id == 0);
		// CHECK(player.mapped_outs[1].out.module_id == 1);
		// CHECK(player.mapped_outs[1].out.jack_id == 3);

		// CHECK(player.mapped_outs[2].panel_jack_id == 2);
		// CHECK(player.mapped_outs[2].out.module_id == 2);
		// CHECK(player.mapped_outs[2].out.jack_id == 1);

		SUBCASE("Check if output connection data is correct")
		{
			Jack panel_out_0 = player.get_panel_output_connection(0);
			CHECK(panel_out_0.module_id == 1);
			CHECK(panel_out_0.jack_id == 3);

			Jack panel_out_1 = player.get_panel_output_connection(1);
			CHECK(panel_out_1.module_id == 1);
			CHECK(panel_out_1.jack_id == 1);

			Jack panel_out_2 = player.get_panel_output_connection(2);
			CHECK(panel_out_2.module_id == 2);
			CHECK(panel_out_2.jack_id == 1);

			SUBCASE("Unmapped jacks are connected to 0,0")
			{
				Jack panel_out_3 = player.get_panel_output_connection(3);
				CHECK(panel_out_3.module_id == 0);
				CHECK(panel_out_3.jack_id == 0);
			}
		}
	}
}

#include "patches/unittest_outmap_overlapping_cable.hh"
TEST_CASE("Internal cables: single and stacked")
{
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_overlapping_cable_mmpatch);

	// In VCV Rack, if two cables are stacked, they appear as two separate cables.
	// Contrary to this, we consider them as a single cable, with one output and two inputs.
	// So, this patch should have 2 cables (a 1->1 and a 1->2)
	CHECK(ph->num_int_cables == 2);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);

	bool found_cable1 = false;
	bool found_cable2 = false;
	Jack end_of_cable = Jack{-1, -1};

	for (int net_i = 0; net_i < ph->num_int_cables; net_i++) {
		auto &cable = player.int_cables[net_i];

		// Check for cable1: 1->1 cable
		// {1,3} -> {2,0}
		if (cable.out == Jack{1, 3}) {
			if (cable.ins[0] == Jack{2, 0}) {
				if (cable.ins[1] == end_of_cable)
					found_cable1 = true;
			}
		}

		// Check for cable2: 1->2 cable
		// {1,1} -> {2,1},{2,2}  or  {2,2},{2,1}
		if (cable.out == Jack{1, 1}) {
			if ((cable.ins[0] == Jack{2, 1} && cable.ins[1] == Jack{2, 2}) ||
				(cable.ins[0] == Jack{2, 2} && cable.ins[1] == Jack{2, 1}))
			{
				if (cable.ins[2] == end_of_cable)
					found_cable2 = true;
			}
		}
	}

	CHECK(found_cable1);
	CHECK(found_cable2);
}

TEST_CASE("Output jack mapping to an virtual input jack that has a valid cable")
{
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_overlapping_cable_mmpatch);

	CHECK(ph->num_mapped_outs == 3);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

	SUBCASE("Check if output connection data is correct")
	{
		CHECK(player.get_panel_output_connection(0) == Jack{1, 3});
		CHECK(player.get_panel_output_connection(1) == Jack{1, 1});
		CHECK(player.get_panel_output_connection(2) == Jack{2, 1});

		SUBCASE("Unmapped jack is connected to 0,0")
		{
			CHECK(player.get_panel_output_connection(3) == Jack{0, 0});
		}
	}
}

#include "patches/unittest_inmapping.hh"
// Note: we do not support multiple input mappings in VCV (yet), so aren't testing for it now
// because there's no easy way to create the test data
TEST_CASE("Simple input jack mapping")
{
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_inmapping_mmpatch);
	REQUIRE(ph->num_mapped_ins == 6);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
	player.calc_panel_jack_connections();

	SUBCASE("Check if input connection data is correct")
	{
		CHECK(player.get_panel_input_connection(0) == Jack{1, 0});
		CHECK(player.get_panel_input_connection(1) == Jack{1, 2});
		CHECK(player.get_panel_input_connection(2) == Jack{2, 1});
		CHECK(player.get_panel_input_connection(3) == Jack{2, 0});
		CHECK(player.get_panel_input_connection(7) == Jack{1, 1});
		CHECK(player.get_panel_input_connection(8) == Jack{1, 3});

		SUBCASE("Unmapped jacks are connected to 0,0")
		{
			CHECK(player.get_panel_input_connection(4) == Jack{0, 0});
			CHECK(player.get_panel_input_connection(5) == Jack{0, 0});
			CHECK(player.get_panel_input_connection(6) == Jack{0, 0});

			SUBCASE("All connections are 1->1")
			{
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

/*
TEST_CASE("Panel jack connections")
{
	MetaModule::PatchPlayer player;
	player.calc_panel_jack_connections();

	for (int i = 0; i < Panel::NumInJacks; i++) {
		// printf("in_conns[%d] = {%d, %d}\n", i, player.in_conns[i].module_id, player.in_conns[i].jack_id);
		if (i != 1) {
			CHECK(player.get_panel_input_connection(i).module_id == 0);
			CHECK(player.get_panel_input_connection(i).jack_id == 0);
		} else {
			CHECK(player.get_panel_input_connection(i).module_id == 5);
			CHECK(player.get_panel_input_connection(i).jack_id == 2);
		}
	}

	for (int i = 0; i < Panel::NumOutJacks; i++) {
		// printf("out_conns[%d] = {%d, %d}\n", i, player.out_conns[i].module_id, player.out_conns[i].jack_id);
		if (i != 1) {
			CHECK(player.get_panel_output_connection(i).module_id == 0);
			CHECK(player.get_panel_output_connection(i).jack_id == 0);
		} else {
			CHECK(player.get_panel_output_connection(i).module_id == 3);
			CHECK(player.get_panel_output_connection(i).jack_id == 6);
		}
	}
}

TEST_CASE("Dup module index")
{
	SUBCASE("Dual LFOs, one panel")
	{
		const Patch exampleDualLFO = {
			.modules_used =
				{
					"PANEL_8",
					"LFOSINE",
					"LFOSINE",
				},
			.num_modules = 3,
		};
		MetaModule::PatchPlayer player;
		player.calc_multiple_module_indicies(exampleDualLFO);
		CHECK(player.get_multiple_module_index(0) == 0); // PANEL_8
		CHECK(player.get_multiple_module_index(1) == 1); // LFOSINE 1
		CHECK(player.get_multiple_module_index(2) == 2); // LFOSINE 2
	}

	SUBCASE("If there's more than one of a module type, caches correct 'dup index' for each")
	{
		MetaModule::PatchPlayer player;
		player.calc_multiple_module_indicies(p);

		CHECK(player.get_multiple_module_index(0) == 0); // PANEL_8
		CHECK(player.get_multiple_module_index(1) == 1); // LFOSINE 1
		CHECK(player.get_multiple_module_index(2) == 1); // KARPLUS 1
		CHECK(player.get_multiple_module_index(3) == 2); // LFOSINE 2
		CHECK(player.get_multiple_module_index(4) == 0); // CLOCK
		CHECK(player.get_multiple_module_index(5) == 3); // LFOSINE 3
		CHECK(player.get_multiple_module_index(6) == 4); // LFOSINE 4
		CHECK(player.get_multiple_module_index(7) == 2); // KARPLUS 2

		SUBCASE("Unloading a patch clears the indices to 0")
		{
			player.unload_patch(p);
			CHECK(player.get_multiple_module_index(0) == 0); // PANEL_8
			CHECK(player.get_multiple_module_index(1) == 0); // LFOSINE 1
			CHECK(player.get_multiple_module_index(2) == 0); // KARPLUS 1
			CHECK(player.get_multiple_module_index(3) == 0); // LFOSINE 2
			CHECK(player.get_multiple_module_index(4) == 0); // CLOCK
			CHECK(player.get_multiple_module_index(5) == 0); // LFOSINE 3
			CHECK(player.get_multiple_module_index(6) == 0); // LFOSINE 4
			CHECK(player.get_multiple_module_index(7) == 0); // KARPLUS 2
		}
	}
}

TEST_CASE("MappedParam get_mapped_val")
{

	MappedKnob knob;
	float mapped_low;
	float mapped_high;
	SUBCASE("Normal mappings (partial range)")
	{
		mapped_low = 0.3f;
		mapped_high = 0.8f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.3));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.55));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.8));

		mapped_low = 0.9f;
		mapped_high = 1.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.9));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.95));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(1.0));
	}

	SUBCASE("Mapped to full range (trivial mapping)")
	{
		mapped_low = 0.0f;
		mapped_high = 1.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(1.0));
	}

	SUBCASE("Zero mapping")
	{
		mapped_low = 0.0f;
		mapped_high = 0.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.0));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.0));
	}

	SUBCASE("Reverse direction mapping (0..1 => 1..0)")
	{
		mapped_low = 1.0f;
		mapped_high = 0.0f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(1.0));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.0));
	}
	SUBCASE("Partial range, reverse direction(0..1 => 1.0..0.5)")
	{
		mapped_low = 0.5f;
		mapped_high = 0.1f;
		knob.range = mapped_high - mapped_low;
		knob.offset = mapped_low;
		CHECK(knob.get_mapped_val(0.0f) == doctest::Approx(0.5));
		CHECK(knob.get_mapped_val(0.5f) == doctest::Approx(0.3));
		CHECK(knob.get_mapped_val(1.0f) == doctest::Approx(0.1));
	}
}
*/
