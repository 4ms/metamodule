#include "patch.hh"
static const Patch fadedelay_example = {
	.modules_used =
		{
			"PANEL_8",
			"FADEDELAY",
			"FADEDELAY",
		},
	.num_modules = 3,

	.module_nodes = {{
		// PANEL_8
		{
			1,
			2,
			1,
			2,
			255,
			254,
			253,
			252,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		},
		// FADEDELAY
		{
			2,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		},
		// FADEDELAY
		{
			1,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 0},
				{.module_id = 2, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 1},
				{.module_id = 1, .jack_id = 0},
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
				{.module_id = 1, .jack_id = 0},
				{.module_id = 0, .jack_id = 1},
			}},
		},
	}},
	.num_nets = 4,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.382500f},
		{.module_id = 1, .param_id = 1, .value = 0.352500f},
		{.module_id = 1, .param_id = 2, .value = 0.355500f},
		{.module_id = 1, .param_id = 3, .value = 0.432000f},
		{.module_id = 2, .param_id = 0, .value = 0.258000f},
		{.module_id = 2, .param_id = 1, .value = 0.322500f},
		{.module_id = 2, .param_id = 2, .value = 0.232500f},
		{.module_id = 2, .param_id = 3, .value = 0.373500f},
	}},
	.num_static_knobs = 8,

	.mapped_knobs = {{
		{.module_id = 2, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 2, .param_id = 1, .panel_knob_id = 1},
		{.module_id = 2, .param_id = 2, .panel_knob_id = 2},
		{.module_id = 2, .param_id = 3, .panel_knob_id = 3},
		{.module_id = 1, .param_id = 0, .panel_knob_id = 4},
		{.module_id = 1, .param_id = 1, .panel_knob_id = 5},
		{.module_id = 1, .param_id = 2, .panel_knob_id = 6},
		{.module_id = 1, .param_id = 3, .panel_knob_id = 7},
	}},
	.num_mapped_knobs = 8,

};
