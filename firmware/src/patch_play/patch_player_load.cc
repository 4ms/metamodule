#include "coreproc_plugin/async_thread_control.hh"
#include "delay.hh"
#include "patch_play/patch_player.hh"
#include "system/abort_rescue.hh"
#include "util/countzip.hh"
#include <csetjmp>

namespace MetaModule
{

PatchPlayer::PatchPlayer() {
	clear_cache();
}

PatchPlayer::~PatchPlayer() {
	if (is_loaded) {
		unload_patch();
	}
}

void PatchPlayer::copy_patch_data(const PatchData &patchdata) {
	if (is_loaded)
		unload_patch();

	//Copy so that the currently playing PatchData is immune to edits of the saved version
	pd = patchdata;
}

Result PatchPlayer::load_patch(const PatchData &patchdata) {

	// load_patch must only be called from the GUI context (Core 1, not in an interrupt).
	// AsyncThreads will interrupt the GUI context on Core 1, and run concurrently on Core 0.
	// Otherwise if the current context blocks AsyncThreads, then is_any_thread_executing() may hang forever
	// and/or an AsyncThread could crash since its module * is no longer valid after we call unload_patch
	pause_module_threads();
	while (is_any_thread_executing()) {}

	if (patchdata.patch_name.length() == 0)
		return {false, "Cannot load: patch does not have a name"};

	if (patchdata.module_slugs.size() == 0)
		return {false, "Cannot load: patch does not have any modules"};

	copy_patch_data(patchdata);

	num_modules = pd.module_slugs.size();

	if (num_modules > MAX_MODULES_IN_PATCH) {
		return {false, "Too many modules in the patch! Max is 64"};
	}

	// First module is the hub
	modules[0] = try_create_module(PanelDef::typeID);
	if (modules[0] != nullptr)
		modules[0]->id = 0;

	unsigned num_not_found = 0;
	std::string not_found;
	for (size_t i = 1; i < num_modules; i++) {
		modules[i] = try_create_module(pd.module_slugs[i]);

		if (modules[i] == nullptr) {
			pr_err("Module %s not found\n", pd.module_slugs[i].data());
			modules[i] = std::make_unique<NullModule>();
			num_not_found++;
			if (num_not_found == 1)
				not_found = std::string_view{pd.module_slugs[i]};
		} else {
			pr_trace("Loaded module[%zu]: %s\n", i, pd.module_slugs[i].data());

			modules[i]->id = i;
			modules[i]->mark_all_inputs_unpatched();
			modules[i]->mark_all_outputs_unpatched();
			modules[i]->set_samplerate(samplerate);
		}
	}

	mark_patched_jacks();
	calc_panel_jack_connections();

	// Re-apply physical state so panel-mapped jacks come up patched immediately
	mark_patched_panel_jacks();

	for (auto [knob_set_idx, knob_set] : enumerate(pd.knob_sets)) {
		for (auto const &k : knob_set.set) {
			cache_knob_mapping(knob_set_idx, k);
		}
	}

	pd.update_midi_poly_num();

	for (auto const &mm : pd.midi_maps.set) {
		cache_midi_mapping(mm);
		param_watcher.start_watching_param(mm);
	}

	// Init modules
	for (size_t module_idx = 1; module_idx < num_modules; module_idx++) {
		// Load module state (for vcv modules, this calls dataFromJson)
		// To mimic VCV, this must be done before plugin_module_init (which calls onAdd)
		auto ms = std::ranges::find(pd.module_states, module_idx, &ModuleInitState::module_id);
		if (ms != pd.module_states.end())
			modules[module_idx]->load_state(ms->state_data);

		plugin_module_init(modules[module_idx]);
	}

	// Set static (non-mapped) knobs
	for (auto const &k : pd.static_knobs)
		modules[k.module_id]->set_param(k.param_id, k.value);

	// Apply bypass state
	for (auto id : pd.bypassed_modules) {
		if (id < num_modules)
			modules[id]->bypassed = true;
	}

	calc_multiple_module_indicies();

	active_knob_set = 0;
	catchup_manager.reset(modules, knob_maps[active_knob_set]);

	rebalance_modules();

	resume_module_threads(0);
	// Some delay to reduce simultaneous load on both cores
	delay_ms(100);
	resume_module_threads(1);

	live_load.reset();
	is_loaded = true;
	if (num_not_found == 1)
		return {true, std::string{"Module "} + not_found + std::string{" not known, ignoring."}};
	else if (num_not_found > 1)
		return {true,
				std::string{"Module "} + not_found + std::string{" and "} + std::to_string(num_not_found - 1) +
					std::string{" others not known, ignoring."}};

	else
		return {true};
}

void PatchPlayer::unload_patch() {
	param_watcher.stop_watching_all();

	smp.join();
	is_loaded = false;
	for (size_t i = 0; i < num_modules; i++) {
		plugin_module_deinit(modules[i]);
		modules[i].reset(nullptr);
	}
	cables.clear();

	pd.module_slugs.clear();
	pd.int_cables.clear();
	pd.mapped_ins.clear();
	pd.mapped_outs.clear();
	pd.static_knobs.clear();
	pd.knob_sets.clear();
	pd.module_slugs.clear();
	pd.mapped_lights.clear();
	pd.module_states.clear();
	pd.bypassed_modules.clear();
	pd.midi_maps.set.clear();
	pd.midi_maps.name = "";

	num_modules = 0;

	clear_cache();
}

void PatchPlayer::set_samplerate(float hz) {
	samplerate = hz;

	for (auto &mp : midi_pulses)
		mp.pulse.set_update_rate_hz(samplerate);

	for (auto &mp : midi_divclk_pulses)
		mp.pulse.set_update_rate_hz(samplerate);

	for (auto &p : midi_poly_retrig.pulses)
		p.set_update_rate_hz(samplerate);

	for (size_t i = 1; i < num_modules; i++) {
		modules[i]->set_samplerate(samplerate);
	}
}

std::unique_ptr<CoreProcessor> PatchPlayer::try_create_module(std::string_view combined_slug, CreateResult *result) {
	if (result)
		*result = CreateResult::Ok;

	// A plugin module's constructor whose exception cannot cross the
	// plugin boundary (pre-2.3 SDK), or that dies without a catchable
	// exception, runs the plugin's terminate -> its imported abort() ->
	// mm_plugin_abort, which longjmps back here. Whatever the constructor
	// had allocated leaks into the plugin arena (bounded, reported on
	// console).
	AbortRescue rescue;
	if (setjmp(rescue.jb) != 0) {
		pr_err("Module %.*s crashed while being created\n", (int)combined_slug.size(), combined_slug.data());
		if (result)
			*result = CreateResult::Crashed;
		return nullptr;
	}
	rescue.arm();

	try {
		auto module = ModuleFactory::create(combined_slug);
		if (!module && result)
			*result = CreateResult::NotFound; // unknown slug
		return module;
	} catch (std::bad_alloc &) {
		pr_err("Out of memory creating module %.*s\n", (int)combined_slug.size(), combined_slug.data());
		if (result)
			*result = CreateResult::OutOfMemory;
		return nullptr;
	} catch (std::exception &e) {
		// Plugins built with SDK >= 2.3 can propagate exceptions across
		// the boundary (unified exidx lookup): destructors run during
		// unwind, so this path reclaims what the constructor allocated
		pr_err("Exception creating module %.*s: %s\n", (int)combined_slug.size(), combined_slug.data(), e.what());
		if (result)
			*result = CreateResult::Crashed;
		return nullptr;
	} catch (...) {
		pr_err("Exception creating module %.*s\n", (int)combined_slug.size(), combined_slug.data());
		if (result)
			*result = CreateResult::Crashed;
		return nullptr;
	}
}

// Check for multiple instances of same module type, and cache the results
// This is used to create unique names for modules (e.g. LFO#1, LFO#2,...)
void PatchPlayer::calc_multiple_module_indicies() {

	num_modules = pd.module_slugs.size(); //refresh this anytime we are refreshing dup_module_index

	// Todo: this is a naive implementation, perhaps can be made more efficient
	for (size_t i = 0; i < num_modules; i++) {

		unsigned found = 1;
		unsigned this_index = 0;
		for (size_t j = 0; j < num_modules; j++) {
			if (i == j) {
				this_index = found;
				continue;
			}

			auto &this_slug = pd.module_slugs[i];
			auto &that_slug = pd.module_slugs[j];
			if (that_slug == this_slug) {
				found++;
			}
		}
		if (found == 1)
			this_index = 0;
		dup_module_index[i] = this_index;
	}
}

} // namespace MetaModule
