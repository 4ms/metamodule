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
				{.module_id = 0, .jack_id = 1},
				{.module_id = 5, .jack_id = 3},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 3, .jack_id = 6},
				{.module_id = 0, .jack_id = 2},
			}},
		},
	}},
	.num_nets = 2,
};

TEST_CASE("Panel jack connections")
{
	// should see:
	// panel input#2 (which is Audio Out, for example) --> module 5 input#1
	// module 3 output#6 --> panel output#4 (which is CV In C, for example)

	PatchPlayer player;
	player.calc_panel_jack_connections(p);
	CHECK(player.get_panel_input_connection(0).module_id == 0);
	CHECK(player.get_panel_input_connection(1).module_id == 5);
	CHECK(player.get_panel_input_connection(2).module_id == 0);
	CHECK(player.get_panel_input_connection(3).module_id == 0);
	CHECK(player.get_panel_input_connection(4).module_id == 0);
	CHECK(player.get_panel_input_connection(5).module_id == 0);
	CHECK(player.get_panel_input_connection(6).module_id == 0);

	CHECK(player.get_panel_output_connection(0).module_id == 0);
	CHECK(player.get_panel_output_connection(1).module_id == 0);
	CHECK(player.get_panel_output_connection(2).module_id == 3);
	CHECK(player.get_panel_output_connection(3).module_id == 0);
	CHECK(player.get_panel_output_connection(4).module_id == 0);
	CHECK(player.get_panel_output_connection(5).module_id == 0);
	CHECK(player.get_panel_output_connection(6).module_id == 0);
}

TEST_CASE("Dup module index")
{
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
