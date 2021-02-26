#include "patch.hh"
static const Patch example_stereo_verb = {
	.modules_used =
		{
			"PANEL_8",
			"REVERB",
			"REVERB",
		},
	.num_modules = 3,

	.module_nodes = {{
		// PANEL_8
		{
			1, 2, 1, 2, 255, 254, 253, 252, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// REVERB
		{
			2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// REVERB
		{
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
	}},

	.nets = {{
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
				{.module_id = 1, .jack_id = 0},
				{.module_id = 0, .jack_id = 1},
			}},
		},
	}},
	.num_nets = 4,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 1.000000f},  {.module_id = 1, .param_id = 1, .value = 0.200000f},
		{.module_id = 1, .param_id = 2, .value = 0.491500f},  {.module_id = 1, .param_id = 3, .value = 0.178500f},
		{.module_id = 1, .param_id = 4, .value = 0.205500f},  {.module_id = 1, .param_id = 5, .value = 0.243000f},
		{.module_id = 1, .param_id = 6, .value = 1.000000f},  {.module_id = 1, .param_id = 7, .value = 1.000000f},
		{.module_id = 1, .param_id = 8, .value = 1.000000f},  {.module_id = 1, .param_id = 9, .value = 1.000000f},
		{.module_id = 1, .param_id = 10, .value = 1.000000f}, {.module_id = 1, .param_id = 11, .value = 1.000000f},
		{.module_id = 1, .param_id = 12, .value = 1.000000f}, {.module_id = 1, .param_id = 13, .value = 1.000000f},
		{.module_id = 1, .param_id = 14, .value = 1.000000f}, {.module_id = 1, .param_id = 15, .value = 1.000000f},
		{.module_id = 1, .param_id = 16, .value = 1.000000f}, {.module_id = 1, .param_id = 17, .value = 1.000000f},
		{.module_id = 2, .param_id = 0, .value = 1.000000f},  {.module_id = 2, .param_id = 1, .value = 0.200000f},
		{.module_id = 2, .param_id = 2, .value = 0.529500f},  {.module_id = 2, .param_id = 3, .value = 0.171000f},
		{.module_id = 2, .param_id = 4, .value = 0.135000f},  {.module_id = 2, .param_id = 5, .value = 0.213000f},
		{.module_id = 2, .param_id = 6, .value = 1.000000f},  {.module_id = 2, .param_id = 7, .value = 1.000000f},
		{.module_id = 2, .param_id = 8, .value = 1.000000f},  {.module_id = 2, .param_id = 9, .value = 1.000000f},
		{.module_id = 2, .param_id = 10, .value = 1.000000f}, {.module_id = 2, .param_id = 11, .value = 1.000000f},
		{.module_id = 2, .param_id = 12, .value = 1.000000f}, {.module_id = 2, .param_id = 13, .value = 1.000000f},
		{.module_id = 2, .param_id = 14, .value = 1.000000f}, {.module_id = 2, .param_id = 15, .value = 1.000000f},
		{.module_id = 2, .param_id = 16, .value = 1.000000f}, {.module_id = 2, .param_id = 17, .value = 1.000000f},
	}},
	.num_static_knobs = 36,

	.mapped_knobs = {{
		{.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 1, .param_id = 3, .panel_knob_id = 1},
		{.module_id = 1, .param_id = 4, .panel_knob_id = 2},
		{.module_id = 1, .param_id = 5, .panel_knob_id = 3},
		{.module_id = 2, .param_id = 0, .panel_knob_id = 4},
		{.module_id = 2, .param_id = 3, .panel_knob_id = 5},
		{.module_id = 2, .param_id = 4, .panel_knob_id = 6},
		{.module_id = 2, .param_id = 5, .panel_knob_id = 7},
	}},
	.num_mapped_knobs = 8,

};
