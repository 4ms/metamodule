#include "doctest.h"
#include "patch_player.hh"
#include <iostream>

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
TEST_CASE("Output jack mapping")
{
	auto *ph = reinterpret_cast<PatchHeader *>(unittest_outmap_mmpatch);

	MetaModule::PatchPlayer player;
	player.load_patch_from_header(ph);
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
