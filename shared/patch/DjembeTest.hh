#include "patch.hh"
static const Patch DjembeTest = {
	.patch_name = "DjembeTest",
	.modules_used =
		{
			"PANEL_8",
			"DJEMBE",
		},
	.num_modules = 2,

	.module_nodes = {{
		// PANEL_8
		{
			1, 4, 255, 254, 253, 252, 251, 250, 2, 1, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// DJMEBE
		{
			1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 1, .jack_id = 0}, // Djembe Out1 -> Panel Audio Out L
				{.module_id = 0, .jack_id = 0},
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 6}, // Panel Gate In 1 -> Djembe Trig1
				{.module_id = 1, .jack_id = 4},
			}},
		},
	}},
	.num_nets = 2,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.165000f},
		{.module_id = 1, .param_id = 1, .value = 0.250500f},
		{.module_id = 1, .param_id = 2, .value = 0.112500f},
		{.module_id = 1, .param_id = 3, .value = 0.165000f},
	}},
	.num_static_knobs = 4,

	.mapped_knobs = {{
		{.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 1, .param_id = 1, .panel_knob_id = 1},
		{.module_id = 1, .param_id = 2, .panel_knob_id = 2},
		{.module_id = 1, .param_id = 3, .panel_knob_id = 3},
	}},
	.num_mapped_knobs = 4,

};
