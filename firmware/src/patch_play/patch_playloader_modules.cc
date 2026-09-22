#include "patch_play/modules_helpers.hh"
#include "patch_play/patch_playloader.hh"

namespace MetaModule
{

// Returns why the module could not be created (Ok on success), so the
// caller can inform the user
PatchPlayer::CreateResult PatchPlayLoader::load_module(std::string_view slug) {
	AudioPause pause{*this};

	auto created = player_.add_module(slug);

	if (created == PatchPlayer::CreateResult::Ok) {
		auto *patch = patches_.get_view_patch();
		uint16_t module_id = patch->add_module(slug);
		auto info = ModuleFactory::getModuleInfo(slug);

		// Set params to default values
		for (unsigned i = 0; auto const &element : info.elements) {
			if (auto def_val = get_normalized_default_value(element); def_val.has_value()) {
				auto param_id = info.indices[i].param_idx;
				patch->set_or_add_static_knob_value(module_id, param_id, def_val.value());
				player_.apply_static_param({.module_id = module_id, .param_id = param_id, .value = def_val.value()});
			}
			i++;
		}
	}

	copy_load_balance_to_patch();

	pr_info("Heap: %u\n", get_heap_size());

	return created;
}

void PatchPlayLoader::change_module(std::string_view slug, unsigned module_id, bool keep_cables_and_maps) {
	AudioPause pause{*this};

	auto *patch = patches_.get_view_patch();

	if (keep_cables_and_maps) {
		patch->module_slugs[module_id] = slug;
		player_.substitute_module(module_id, slug);
	} else {
		patch->blank_out_module(module_id);
		patch->module_slugs[module_id] = slug;
		player_.replace_module(module_id, slug);
	}

	copy_load_balance_to_patch();

	pr_info("Heap: %u\n", get_heap_size());
}

void PatchPlayLoader::remove_module(unsigned module_id) {
	AudioPause pause{*this, AudioPause::Restart::Always};

	player_.remove_module(module_id);
	copy_load_balance_to_patch();

	pr_info("Heap: %u\n", get_heap_size());
}

void PatchPlayLoader::prepare_patch_for_plugin_change(std::string_view brand_slug) {
	auto playing_patch = patches_.get_playing_patch();
	if (!playing_patch)
		return;

	bool patch_contains_brand = false;

	std::string brand_to_remove = ModuleFactory::cleanupBrandName(brand_slug);
	for (std::string_view combined_slug : playing_patch->module_slugs) {

		if (ModuleFactory::cleanupBrandName(combined_slug) == brand_to_remove) {
			patch_contains_brand = true;
			break;
		}
	}

	if (patch_contains_brand) {
		pr_dbg("Currently playing patch contains a module in the plugin to be removed. Stopping\n");
		stop_audio_and_wait();
		player_.unload_patch();
		// TODO: can we force it to reload from disk, but not forget its location?
		patches_.close_playing_patch();
	}
}

void PatchPlayLoader::get_module_states() {
	if (auto playing_patch = patches_.get_playing_patch()) {
		playing_patch->module_states = player_.patch_query.get_module_states();
		playing_patch->static_knobs = player_.patch_query.get_all_params();
	}
}

} // namespace MetaModule
