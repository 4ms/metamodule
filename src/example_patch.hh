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

// Sized
static const Patch example_patch = {
	.modules_used = {PANEL, LFO, MIXER4, LFO},
	.num_modules = 4,

	// OUT, IN (, IN (, IN ...)): each OUT/IN is {Module_id, jack_id}
	.nets = {{
		// LFO#1 sin out -> Mixer4 in#3
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 1, .jack_id = 0}, {.module_id = 2, .jack_id = 2}}},
		},

		// Mixer4 inverted out -> Panel Left Audio Output jack
		{
			.num_nodes = 2,
			.nodes = {{{.module_id = 2, .jack_id = 0}, {.module_id = 0, .jack_id = 0}}},
		},

		// LFO#2 sin out -> LFO#1 FM in and Mixer4 in#4
		{
			.num_nodes = 3,
			.nodes = {{{.module_id = 3, .jack_id = 0}, {.module_id = 1, .jack_id = 0}, {2, 3}}},
		},

	}},
	.num_nets = 3,

	// Todo: panel mapping to knobs uses .nets also ? Or a different struct?

	.knobs = // module, knob, value
	{{
		{.module_id = 1, .param_id = 0, .value = 0.5f}, // LFO#1 Rate = 50%
		{.module_id = 1, .param_id = 1, .value = 0.5f}, // LFO#1 Phase = 50%
		{.module_id = 2, .param_id = 2, .value = 0.9f}, // Mixer4 Level#3 90%
		{.module_id = 3, .param_id = 0, .value = 0.1f}, // LFO#2 Rate = 10%
	}},
	.num_knobs = 4,

};

