#include "patch.hh"
const Patch exampleDualLFO = {
	.patch_name = "Dual Sine LFO",
	.modules_used =
		{
			"PANEL_8",
			"LFOSINE",
			"LFOSINE",
		},
	.num_modules = 3,

	.module_nodes = {{
		// PANEL_8
		{2, 1, 255, 254, 3, 4, 253, 252, 0, 0, 0, 0, 0, 0},
		// LFOSINE
		{4, 251, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		// LFOSINE
		{3, 250, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 1, .jack_id = 0},
				{.module_id = 0, .jack_id = 1},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 2, .jack_id = 0},
				{.module_id = 0, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 2},
				{.module_id = 2, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 3},
				{.module_id = 1, .jack_id = 0},
			}},
		},
	}},
	.num_nets = 4,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.000000f},
		{.module_id = 1, .param_id = 1, .value = 0.040500f},
		{.module_id = 1, .param_id = 2, .value = 0.312000f},
		{.module_id = 2, .param_id = 0, .value = 0.000000f},
		{.module_id = 2, .param_id = 1, .value = 0.340500f},
		{.module_id = 2, .param_id = 2, .value = 0.306000f},
	}},
	.num_static_knobs = 6,

	.mapped_knobs = {{
		{.module_id = 2, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 1, .param_id = 0, .panel_knob_id = 1},
		{.module_id = 2, .param_id = 2, .panel_knob_id = 2},
		{.module_id = 1, .param_id = 2, .panel_knob_id = 3},
		{.module_id = 2, .param_id = 1, .panel_knob_id = 4},
		{.module_id = 1, .param_id = 1, .panel_knob_id = 5},
	}},
	.num_mapped_knobs = 6,

};
