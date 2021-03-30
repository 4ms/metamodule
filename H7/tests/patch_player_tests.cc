#include "doctest.h"
#include "patch_player.hh"

static const Patch p = {
	.modules_used =
		{
			"PANEL_8",
			"LFOSINE",
			"KARPLUS",
			"LFOSINE",
			"CLOCK",
			"LFOSINE",
			"LFOSINE",
			"KARPLUS",
		},
	.num_modules = 8,

	.module_nodes = {{
		{},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 1}, // producer: panel jack like "Audio In", or virtual jack like "ADSR Out"
				{.module_id = 5, .jack_id = 3}, // consumer: panel jack like "CV Out", or virtual jack like "FM In"
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 3, .jack_id = 6},
				{.module_id = 0, .jack_id = 1},
			}},
		},
	}},
	.num_nets = 2,
};

TEST_CASE("Panel jack connections")
{
	PatchPlayer player;
	player.calc_panel_jack_connections(p);

	for (int i = 0; i < Panel::NumInJacks; i++) {
		// printf("in_conns[%d] = {%d, %d}\n", i, player.in_conns[i].module_id, player.in_conns[i].jack_id);
		if (i != 1) {
			CHECK(player.get_panel_input_connection(i).module_id == 0);
			CHECK(player.get_panel_input_connection(i).jack_id == 0);
		} else {
			CHECK(player.get_panel_input_connection(i).module_id == 5);
			CHECK(player.get_panel_input_connection(i).jack_id == 3);
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
		PatchPlayer player;
		player.calc_multiple_module_indicies(exampleDualLFO);
		CHECK(player.get_multiple_module_index(0) == 0); // PANEL_8
		CHECK(player.get_multiple_module_index(1) == 1); // LFOSINE 1
		CHECK(player.get_multiple_module_index(2) == 2); // LFOSINE 2
	}

	SUBCASE("If there's more than one of a module type, caches correct 'dup index' for each")
	{
		PatchPlayer player;
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
