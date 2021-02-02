#include "patch.hh"
static const Patch example_ps2 = {
	.modules_used =
		{
			"PANEL_8",
			"PITCHSHIFT",
			"LFOSINE",
			"PITCHSHIFT",
		},
	.num_modules = 4,

	.module_nodes = {{
		// nPANEL_8
		{
			3, 5, 0, 0, 0, 0, 2, 4, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// PITCHSHIFT
		{
			2, 1, 8, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// nLFOSINE
		{
			6, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// PITCHSHIFT
		{
			4, 1, 7, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
	}},

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.200000f},
		{.module_id = 1, .param_id = 1, .value = 0.500000f},
		{.module_id = 1, .param_id = 2, .value = 0.300000f},
		{.module_id = 1, .param_id = 3, .value = 0.505500f},
		{.module_id = 2, .param_id = 0, .value = 0.400000f},
		{.module_id = 2, .param_id = 1, .value = 0.000000f},
		{.module_id = 2, .param_id = 2, .value = 1.000000f},
		{.module_id = 3, .param_id = 0, .value = 0.500000f},
		{.module_id = 3, .param_id = 1, .value = 0.500000f},
		{.module_id = 3, .param_id = 2, .value = 0.500000f},
		{.module_id = 3, .param_id = 3, .value = 0.499500f},
	}},
	.num_static_knobs = 11,

	.mapped_knobs = {{
		// {.module_id = 3, .param_id = 1, .panel_knob_id = 0},
		// {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
		// {.module_id = 3, .param_id = 2, .panel_knob_id = 2},
		// {.module_id = 1, .param_id = 2, .panel_knob_id = 3},
	}},
	.num_mapped_knobs = 0,

};
