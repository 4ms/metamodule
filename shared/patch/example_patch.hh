#include "patch.hh"
/*
static const Patch example_patch = {
	.modules_used = {"PANEL_8", "LFOSINE", "MIXER4", "LFOSINE"},
	.num_modules = 4,

	// OUT, IN (, IN (, IN ...)): each OUT/IN is {Module_id, jack_id}
	.nets = {{
		// LFO#1 sin out -> Mixer4 in#3 and Panel Right Audio Output jack
		{
			.num_nodes = 3,
			.nodes = {{{.module_id = 1, .jack_id = 0}, {.module_id = 2, .jack_id = 2}, {.module_id = 0, .jack_id = 1}}},
		},

		// Mixer4 inverted out -> Panel Left Audio Output jack
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 2, .jack_id = 0}, {.module_id = 0, .jack_id = 0}}},
		},

		// LFO#2 sin out -> LFO#1 FM in and Mixer4 in#4
		{
			.num_nodes = 3,
			.nodes = {{{.module_id = 3, .jack_id = 0}, {.module_id = 1, .jack_id = 0}, {.module_id = 2, .jack_id = 3}}},
		},

	}},
	.num_nets = 3,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.8f}, // LFO#1 Rate = 50%
		{.module_id = 1, .param_id = 1, .value = 0.5f}, // LFO#1 Phase = 50%
		{.module_id = 2, .param_id = 0, .value = 0.0f}, // Mixer4 Level#1
		{.module_id = 2, .param_id = 1, .value = 0.0f}, // Mixer4 Level#2
		{.module_id = 2, .param_id = 2, .value = 0.0f}, // Mixer4 Level#3
		{.module_id = 2, .param_id = 3, .value = 0.7f}, // Mixer4 Level#4
		{.module_id = 3, .param_id = 0, .value = 0.1f}, // LFO#2 Rate = 10%
	}},
	.num_static_knobs = 7,

	.mapped_knobs = {{
		{.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 3, .param_id = 0, .panel_knob_id = 1},
		{.module_id = 2, .param_id = 2, .panel_knob_id = 2},
		{.module_id = 2, .param_id = 3, .panel_knob_id = 3},
	}},
	.num_mapped_knobs = 4,
};


*/

enum NodeNames2 {
	INL,
	INR,
	CV0,
	CV1,
	CV2,
	CV3,
	OUTL,
	OUTR,
	LFO1_TO_MIXERCH0,
	LFO2_TO_MIXERCH1,
	FREE0,
	FREE1,
	FREE2,
	FREE3,
};
static const Patch example_patch2 = {
	.modules_used = {"nPANEL_8", "nLFOSINE", "nLFOSINE", "nMIXER4"},
	.num_modules = 4,

	.module_nodes = {{
		// PANEL_8
		{INL, INR, CV0, CV1, CV2, CV3, OUTL, OUTR},

		// LFO#1
		{FREE0, FREE1, LFO1_TO_MIXERCH0},

		// LFO#2
		{FREE0, FREE1, LFO2_TO_MIXERCH1},

		// MIXER
		{LFO1_TO_MIXERCH0, LFO2_TO_MIXERCH1, FREE2, FREE3, OUTL, OUTR},
	}},
	.nets = {{

	}},
	.num_nets = 0,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.5f}, // LFO#1 Rate
		{.module_id = 1, .param_id = 1, .value = 0.3f}, // LFO#1 Phase
		{.module_id = 2, .param_id = 0, .value = 0.6f}, // LFO#2 Rate
		{.module_id = 2, .param_id = 1, .value = 0.0f}, // LFO#2 Phase
		{.module_id = 3, .param_id = 0, .value = 0.5f}, // Mixer4 Level#1
		{.module_id = 3, .param_id = 1, .value = 0.5f}, // Mixer4 Level#2
		{.module_id = 3, .param_id = 2, .value = 0.0f}, // Mixer4 Level#3
		{.module_id = 3, .param_id = 3, .value = 0.0f}, // Mixer4 Level#4
	}},
	.num_static_knobs = 8,

	.mapped_knobs = {{
		{.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 3, .param_id = 0, .panel_knob_id = 1},
		{.module_id = 2, .param_id = 0, .panel_knob_id = 2},
		{.module_id = 3, .param_id = 1, .panel_knob_id = 3},
	}},
	.num_mapped_knobs = 4,
};

static const Patch example_patch3 = {
	.modules_used = {"PANEL_8", "PITCHSHIFT", "LFOSINE"},
	.num_modules = 3,

	.module_nodes = {{
		// PANEL_8
		{INL, INR, CV0, CV1, CV2, CV3, OUTL, OUTR},

		// PITCHSHIFT
		{INL, FREE1, CV1, CV2, OUTL},

		// LFO
		{CV0, FREE0, FREE1},
	}},

	.nets = {{

	}},
	.num_nets = 0,

	.static_knobs = {{}},
	.num_static_knobs = 0,

	.mapped_knobs = {{
		{.module_id = 1, .param_id = 0, .panel_knob_id = 0},
		{.module_id = 1, .param_id = 1, .panel_knob_id = 1},
		{.module_id = 1, .param_id = 2, .panel_knob_id = 2},
		{.module_id = 1, .param_id = 3, .panel_knob_id = 3},
	}},
	.num_mapped_knobs = 4,
};

