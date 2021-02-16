#include "patch.hh"
const Patch exampleDrum = {
	.modules_used =
		{
			"PANEL_8",
			"LFOSINE",
			"DRUM",
		},
	.num_modules = 3,

	.module_nodes = {{
		// PANEL_8
		{
			1, 255, 254, 253, 252, 251, 250, 249, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0,	0,	 0,	  0,   0,	0,	 0,	  0, 0, 0, 0, 0, 0, 0, 0,
		},
		// LFOSINE
		{
			248, 247, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// DRUM
		{
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 1, .jack_id = 0},
				{.module_id = 2, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 2, .jack_id = 0},
				{.module_id = 0, .jack_id = 0},
			}},
		},
	}},
	.num_nets = 2,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.000000f},
		{.module_id = 1, .param_id = 1, .value = 0.000000f},
		{.module_id = 1, .param_id = 2, .value = 1.000000f},
		{.module_id = 2, .param_id = 0, .value = 0.127500f},
		{.module_id = 2, .param_id = 1, .value = 0.337500f},
		{.module_id = 2, .param_id = 2, .value = 0.262500f},
		{.module_id = 2, .param_id = 3, .value = 0.325500f},
		{.module_id = 2, .param_id = 4, .value = 0.093000f},
		{.module_id = 2, .param_id = 5, .value = 0.433500f},
		{.module_id = 2, .param_id = 6, .value = 0.282000f},
		{.module_id = 2, .param_id = 7, .value = 0.184500f},
		{.module_id = 2, .param_id = 8, .value = 0.216000f},
	}},
	.num_static_knobs = 12,

	.mapped_knobs = {{
		{.module_id = 2, .param_id = 1, .panel_knob_id = 1},
		{.module_id = 1, .param_id = 0, .panel_knob_id = 3},
		{.module_id = 2, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 2, .param_id = 2, .panel_knob_id = 2},
		{.module_id = 2, .param_id = 3, .panel_knob_id = 4},
	}},
	.num_mapped_knobs = 5,

};
