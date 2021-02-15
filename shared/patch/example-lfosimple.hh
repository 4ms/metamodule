#include "patch.hh"
const Patch example_lfosimple = {
	.modules_used =
		{
			"PANEL_8",
			"LFOSINE",
			"LFOSINE",
		},
	.num_modules = 3,

	.module_nodes = {{
		// PANEL_8
		{
			1, 3, 4, 5, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// LFOSINE
		{
			2, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
		// LFOSINE
		{
			6, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		},
	}},

	.nets = {{
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 1, .jack_id = 0}, // LFO::get_output(0) SINEOUT
				{.module_id = 0, .jack_id = 0}, //-->Panel::set_output(0) OUTL
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 0}, // Panel::get_input(0) INL
				{.module_id = 1, .jack_id = 0}, //-->LFO::set_input(0) FM
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 2, .jack_id = 0}, // LFO::get_output(0) SINEOUT
				{.module_id = 0, .jack_id = 1}, //-->Panel::set_output(1) OUTR
			}},
		},
		{
			.num_jacks = 2,
			.jacks = {{
				{.module_id = 0, .jack_id = 1},
				{.module_id = 2, .jack_id = 0},
			}},
		},
	}},
	.num_nets = 4,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.500000f},
		{.module_id = 1, .param_id = 1, .value = 0.700000f},
		{.module_id = 1, .param_id = 2, .value = 0.400000f},
		{.module_id = 2, .param_id = 0, .value = 0.700000f},
		{.module_id = 2, .param_id = 1, .value = 0.700000f},
		{.module_id = 2, .param_id = 2, .value = 0.400000f},
	}},
	.num_static_knobs = 6,

	.mapped_knobs = {{
		// {.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		// {.module_id = 1, .param_id = 1, .panel_knob_id = 1},
		// {.module_id = 1, .param_id = 2, .panel_knob_id = 2},
	}},
	.num_mapped_knobs = 0,

};
