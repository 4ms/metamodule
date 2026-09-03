#include "patch_play/patch_player.hh"

namespace MetaModule
{

PatchPlayer::CreateResult PatchPlayer::add_module(BrandModuleSlug slug) {
	auto module_idx = num_modules;

	pd.module_slugs.push_back(slug);
	calc_multiple_module_indicies();

	CreateResult result{CreateResult::Ok};
	if (!add_module_at_idx(slug, module_idx, &result)) {
		modules[module_idx].reset();
		pd.module_slugs.pop_back();
		calc_multiple_module_indicies();
	}
	return result;
}

bool PatchPlayer::add_module_at_idx(BrandModuleSlug slug, unsigned module_idx, CreateResult *result) {
	modules[module_idx] = try_create_module(slug, result);
	if (modules[module_idx] == nullptr) {
		pr_err("Could not create module %s\n", slug.c_str());
		modules[module_idx] = std::make_unique<NullModule>();
		modules[module_idx]->id = module_idx;
		return false;
	}
	pr_trace("Loaded module[%zu]: %s\n", module_idx, slug.c_str());

	modules[module_idx]->id = module_idx;

	// Match order that VCV does: fromJson (via load_state), then onAdd (via plugin_module_init)
	reset_module(module_idx);
	plugin_module_init(modules[module_idx]);

	modules[module_idx]->mark_all_inputs_unpatched();
	modules[module_idx]->mark_all_outputs_unpatched();
	modules[module_idx]->set_samplerate(samplerate);

	rebalance_modules();

	// Mark jacks patched
	mark_patched_jacks(module_idx);
	mark_patched_panel_jacks(module_idx);
	return true;
}

void PatchPlayer::remove_module(uint16_t module_idx) {
	// For all cache structures, if (module_id > deleted_module_idx) module_id -= 1;

	auto squash_module_id = [gap = module_idx](auto &module_id) {
		if (module_id > gap && module_id != disconnected_jack.module_id)
			module_id--;
	};

	auto erase_and_squash = [=](auto &container) {
		for (auto &item : container) {
			std::erase_if(item, [=](auto &map) { return (map.module_id == module_idx); });
			for (auto &map : item) {
				squash_module_id(map.module_id);
			}
		}
	};

	// Panel Input connections
	erase_and_squash(in_conns);

	// Panel Output connections
	erase_and_squash(out_conns);

	// Internal cables
	// Inform other modules connected to this one
	// that their jacks are to be disconnected
	for (auto &cable : pd.int_cables) {

		unsigned ins_to_disconnect = 0;
		for (auto in : cable.ins) {
			if (cable.out.module_id == module_idx) {
				modules[in.module_id]->mark_input_unpatched(in.jack_id);
			}

			if (in.module_id == module_idx) {
				ins_to_disconnect++;
			}
		}

		if (ins_to_disconnect == cable.ins.size()) {
			modules[cable.out.module_id]->mark_output_unpatched(cable.out.jack_id);
		}
	}

	// Knob and MIDI connections
	for (auto &param_set : knob_maps) {
		// erase_and_squash(knob_set);
		for (auto &set : param_set) {
			std::erase_if(set, [=](auto &map) { return (map.map.module_id == module_idx); });
			for (auto &map : set) {
				squash_module_id(map.map.module_id);
			}
		}
	}

	midi.erase_module(module_idx, squash_module_id);

	pd.remove_module(module_idx);

	plugin_module_deinit(modules[module_idx]);
	modules[module_idx].reset();

	// Move [i+1...end) to i
	std::move(std::next(modules.begin(), module_idx + 1), modules.end(), std::next(modules.begin(), module_idx));

	calc_multiple_module_indicies();

	for (auto i = 0u; i < num_modules; i++) {
		if (modules[i])
			modules[i]->id = i;
	}

	refresh_conn_flags();

	rebalance_modules();
}

// replace a module without changing any mappings or cables
void PatchPlayer::substitute_module(unsigned module_idx, BrandModuleSlug new_slug) {
	if (module_idx >= num_modules)
		return;

	pr_trace("Subs. module %u (%s) with %s\n", module_idx, pd.module_slugs[module_idx].c_str(), new_slug.c_str());

	// De-init original module
	plugin_module_deinit(modules[module_idx]);
	modules[module_idx].reset();

	// Add new module
	pd.module_slugs[module_idx] = new_slug;
	// The new module's CPU load is unknown, so the balance has to be measured again
	pd.clear_load_balance();
	calc_multiple_module_indicies();
	add_module_at_idx(new_slug, module_idx);
}

void PatchPlayer::replace_module(uint16_t module_idx, BrandModuleSlug new_slug) {
	if (module_idx >= num_modules)
		return;

	pr_trace("Replace module %u (%s) with %s\n", module_idx, pd.module_slugs[module_idx].c_str(), new_slug.c_str());

	//  Erase cached connections referencing this module (unlike remove_module, there is no squashing)

	auto erase_matching = [=](auto &container) {
		for (auto &item : container) {
			std::erase_if(item, [=](auto &map) { return (map.module_id == module_idx); });
		}
	};

	// Panel connections
	erase_matching(in_conns);
	erase_matching(out_conns);

	// Inform other modules their jacks are disconnected
	for (auto &cable : pd.int_cables) {
		unsigned ins_to_disconnect = 0;
		for (auto in : cable.ins) {
			if (cable.out.module_id == module_idx) {
				modules[in.module_id]->mark_input_unpatched(in.jack_id);
			}
			if (in.module_id == module_idx) {
				ins_to_disconnect++;
			}
		}
		if (ins_to_disconnect == cable.ins.size()) {
			modules[cable.out.module_id]->mark_output_unpatched(cable.out.jack_id);
		}
	}

	// Knob maps
	for (auto &param_set : knob_maps) {
		for (auto &set : param_set) {
			std::erase_if(set, [=](auto &map) { return (map.map.module_id == module_idx); });
		}
	}

	// MIDI maps
	midi.erase_module(module_idx);

	// Deinit old module
	plugin_module_deinit(modules[module_idx]);
	modules[module_idx].reset();

	// Clean up PatchData (cables, mapped_ins/outs, static_knobs, etc.)
	pd.blank_out_module(module_idx);

	// Create new module in the same slot
	pd.module_slugs[module_idx] = new_slug;
	calc_multiple_module_indicies();
	add_module_at_idx(new_slug, module_idx);

	refresh_conn_flags();
}

void PatchPlayer::reset_module(uint16_t module_id, std::string_view data) {
	if (module_id < num_modules)
		modules[module_id]->load_state(data);
}

void PatchPlayer::set_module_bypass(uint16_t module_id, bool bypassed) {
	if (module_id < num_modules)
		modules[module_id]->bypassed = bypassed;
}

} // namespace MetaModule
