#include "patch.hh"
enum { f0 = 5, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11 };

static const Patch example_ps1 = {
	.modules_used =
		{
			"PANEL_8",
			"PITCHSHIFT",
			"LFOSINE",
			"MIXER4",
		},
	.num_modules = 4,

	.module_nodes = {{
		// PANEL_8
		{
			3, f1, 2, 4, 5, f2, f3, f4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// PITCHSHIFT
		{
			3, 1, 4, 5, f5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// LFOSINE
		{
			2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// MIXER4
		{
			f6,
			f7,
			f8,
			f9,
			f10,
			f11,
		},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 4, .jack_id = 1},
				{.module_id = 1, .jack_id = 1},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 2, .jack_id = 0},
				{.module_id = 4, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 0},
				{.module_id = 1, .jack_id = 0},
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
				{.module_id = 0, .jack_id = 2},
				{.module_id = 2, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 3},
				{.module_id = 1, .jack_id = 2},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 4},
				{.module_id = 1, .jack_id = 3},
			}},
		},
	}},
	.num_nets = 7,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.000000f},
		{.module_id = 1, .param_id = 1, .value = 0.547500f},
		{.module_id = 1, .param_id = 2, .value = 0.210000f},
		{.module_id = 1, .param_id = 3, .value = 0.505500f},
		{.module_id = 2, .param_id = 0, .value = 1.000000f},
		{.module_id = 2, .param_id = 1, .value = 0.000000f},
		{.module_id = 2, .param_id = 2, .value = 1.000000f},
		{.module_id = 4, .param_id = 0, .value = 0.255000f},
		{.module_id = 4, .param_id = 1, .value = 0.000000f},
		{.module_id = 4, .param_id = 2, .value = 0.000000f},
		{.module_id = 4, .param_id = 3, .value = 0.000000f},
	}},
	.num_static_knobs = 11,

	.mapped_knobs = {{
		{.module_id = 2, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 4, .param_id = 0, .panel_knob_id = 1},
		{.module_id = 1, .param_id = 0, .panel_knob_id = 2},
		{.module_id = 1, .param_id = 3, .panel_knob_id = 3},
	}},
	.num_mapped_knobs = 4,

};
