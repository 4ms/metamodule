#include "patch.hh"
static const Patch example_drum_verb_mono = {
	.modules_used =
		{
			"PANEL_8",
			"REVERB",
			"DRUM",
			"MIXER4",
		},
	.num_modules = 4,

	.module_nodes = {{
		// PANEL_8
		{
			3,
			255,
			4,
			254,
			2,
			5,
			253,
			252,
		},
		// REVERB
		{
			1,
			3,
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
		// DRUM
		{
			5,
			2,
			6,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
		},
		// MIXER4
		{
			4,
			6,
			251,
			250,
			249,
			1,
			0,
			0,
			0,
		},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 3, .jack_id = 1},
				{.module_id = 1, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 2, .jack_id = 0},
				{.module_id = 3, .jack_id = 1},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 1, .jack_id = 0},
				{.module_id = 0, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 0},
				{.module_id = 3, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 3},
				{.module_id = 2, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 2},
				{.module_id = 2, .jack_id = 1},
			}},
		},
	}},
	.num_nets = 6,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 1.000000f}, {.module_id = 1, .param_id = 1, .value = 0.260000f},
		{.module_id = 1, .param_id = 2, .value = 0.491500f}, {.module_id = 1, .param_id = 3, .value = 0.178500f},
		{.module_id = 1, .param_id = 4, .value = 0.256500f}, {.module_id = 1, .param_id = 5, .value = 0.243000f},
		{.module_id = 2, .param_id = 0, .value = 0.121500f}, {.module_id = 2, .param_id = 1, .value = 0.346500f},
		{.module_id = 2, .param_id = 2, .value = 0.294000f}, {.module_id = 2, .param_id = 3, .value = 0.117000f},
		{.module_id = 2, .param_id = 4, .value = 0.133500f}, {.module_id = 2, .param_id = 5, .value = 0.232500f},
		{.module_id = 2, .param_id = 6, .value = 0.193500f}, {.module_id = 2, .param_id = 7, .value = 0.165000f},
		{.module_id = 2, .param_id = 8, .value = 0.000000f}, {.module_id = 3, .param_id = 0, .value = 1.000000f},
		{.module_id = 3, .param_id = 1, .value = 1.000000f}, {.module_id = 3, .param_id = 2, .value = 0.000000f},
		{.module_id = 3, .param_id = 3, .value = 0.000000f},
	}},
	.num_static_knobs = 19,

	.mapped_knobs = {{
		{.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 1, .param_id = 3, .panel_knob_id = 1},
		{.module_id = 1, .param_id = 1, .panel_knob_id = 2},
		{.module_id = 1, .param_id = 2, .panel_knob_id = 3},
		{.module_id = 1, .param_id = 4, .panel_knob_id = 4},
		{.module_id = 1, .param_id = 5, .panel_knob_id = 5},
		{.module_id = 2, .param_id = 0, .panel_knob_id = 6},
		{.module_id = 2, .param_id = 8, .panel_knob_id = 7},
	}},
	.num_mapped_knobs = 8,

};
