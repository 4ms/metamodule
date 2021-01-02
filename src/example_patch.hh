#include "patch_player.hh"

// Example of a node-style module:
// class VCAModule : public Module {
// 	const ModuleTypeID type_id = VCA;
// 	enum { OUT, CVIN, AUDIOIN };

// 	void process()
// 	{
// 		if (jack[OUT].is_patched()) {
// 			float cv = jack[CVIN].is_patched() ? jack[CVIN].get() : 1.0f;
// 			float audioin = jack[AUDIOIN].is_patched() ? jack[AUDIOIN].get() : 0.0f;
// 			jack[OUT].set(cv * audioin);
// 		}
// 	}
// };

static const Patch example_patch = {
	.modules_used = {PANEL, LFO, MIXER4, LFO},
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

static const Patch example_patch2 = {
	.modules_used = {ModuleType::PANEL, LFO, LFO, MIXER4},
	.num_modules = 4,

	.nets = {{
		// LFO#1 sin out -> mixer ch0
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 1, .jack_id = 0}, {.module_id = 3, .jack_id = 0}}},
		},
		// LFO#2 sin out -> Mixer ch1
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 2, .jack_id = 0}, {.module_id = 3, .jack_id = 1}}},
		},
		// Mixer inv out -> Left out
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 3, .jack_id = 0}, {.module_id = 0, .jack_id = 0}}},
		},
		// Mixer out -> Right out
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 3, .jack_id = 1}, {.module_id = 0, .jack_id = 1}}},
		},

	}},
	.num_nets = 4,

	.static_knobs = {{
		{.module_id = 1, .param_id = 0, .value = 0.5f}, // LFO#1 Rate
		{.module_id = 1, .param_id = 1, .value = 0.3f}, // LFO#1 Phase
		{.module_id = 2, .param_id = 0, .value = 0.5f}, // LFO#2 Rate
		{.module_id = 2, .param_id = 0, .value = 0.0f}, // LFO#2 Phase
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

