#pragma once
#include "gui/knobset_button.hh"
#include "gui/notify/display.hh"
#include "gui/notify/queue.hh"
#include "gui/slsexport/comp_init.hh"
#include "metaparams.hh"
#include "params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

#include "gui/pages/knobmap.hh"
#include "gui/pages/knobset_view.hh"
#include "gui/pages/main_menu.hh"
#include "gui/pages/module_list.hh"
#include "gui/pages/module_view.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/patch_selector.hh"
#include "gui/pages/patch_view.hh"
#include "gui/pages/system_menu.hh"

namespace MetaModule
{

class PageManager {
	SlsComponentInit sls_comp_init;

	PatchContext info;
	PageList page_list;
	GuiState gui_state;
	ViewSettings settings;
	ButtonLight button_light;

	MainMenuPage page_mainmenu{info};
	PatchSelectorPage page_patchsel{info};
	PatchViewPage page_patchview{info, settings};
	ModuleViewPage page_module{info, settings};
	KnobSetViewPage page_knobsetview{info};
	KnobMapPage page_knobmap{info};
	SystemMenuPage page_systemmenu{info};
	ModuleListPage page_modulelist{info};

public:
	PageBase *cur_page = &page_mainmenu;

	PageManager(FileStorageProxy &patch_storage,
				PatchPlayLoader &patch_playloader,
				ParamsMidiState &params,
				MetaParams &metaparams,
				NotificationQueue &notify_queue,
				PatchModQueue &patch_mod_queue,
				PluginManager &plugin_manager)
		: info{patch_storage,
			   patch_playloader,
			   params,
			   metaparams,
			   notify_queue,
			   patch_mod_queue,
			   page_list,
			   gui_state,
			   plugin_manager} {
	}

	void init() {
		page_list.request_initial_page(PageId::MainMenu, {});
		button_light.display_knobset(0);
	}

	void update_current_page() {

		handle_knobset_change();

		update_patch_params();

		handle_back_event();

		if (auto newpage = page_list.get_requested_page()) {
			if (newpage->page) {
				cur_page->blur();
				cur_page = newpage->page;
				// debug_print_args(newpage);
				cur_page->focus(newpage->args);
			}
		} else
			cur_page->update();

		handle_notifications();
	}

	void handle_knobset_change() {
		auto knobset_change = info.metaparams.rotary_with_metabutton.use_motion();
		if (knobset_change != 0) {

			auto patch = info.patch_storage.playing_patch();
			if (int num_knobsets = patch->knob_sets.size(); num_knobsets > 0) {
				int cur_knobset = info.page_list.get_active_knobset();
				int next_knobset = MathTools::wrap<int>(knobset_change + cur_knobset, 0, num_knobsets - 1);

				info.patch_mod_queue.put(ChangeKnobSet{.knobset_num = (unsigned)next_knobset});
				info.page_list.set_active_knobset(next_knobset);
				std::string ks_name = patch->valid_knob_set_name(next_knobset);

				if (cur_page != page_list.page(PageId::KnobSetView))
					info.notify_queue.put({"Using Knob Set \"" + ks_name + "\"", Notification::Priority::Status, 1000});

				button_light.display_knobset(next_knobset);
			}
		}

		if (button_light.display_knobset() != info.page_list.get_active_knobset()) {
			button_light.display_knobset(info.page_list.get_active_knobset());
		}
	}

	// Update internal copy of patch with knob changes
	// This is used to keep GUI in sync with patch player's copy of the patch without concurrancy issues
	void update_patch_params() {
		auto patch = info.patch_storage.playing_patch();
		auto active_knobset = info.page_list.get_active_knobset();
		if (active_knobset >= patch->knob_sets.size())
			return;

		// Iterate all panel knobs
		for (auto panel_knob_i = 0u; panel_knob_i < info.params.knobs.size(); panel_knob_i++) {

			// Find knobs that have moved
			auto knobpos = info.params.panel_knob_new_value(panel_knob_i);
			if (!knobpos.has_value())
				continue;

			auto UpdateMapping = [=, &patch](auto const &map) {
				if (map.panel_knob_id == panel_knob_i) {
					auto scaled_val = map.get_mapped_val(knobpos.value());
					patch->set_or_add_static_knob_value(map.module_id, map.param_id, scaled_val);
				}
			};

			// Update patch for any map that's mapped to the knob that moved
			for (auto &map : patch->knob_sets[active_knobset].set) {
				UpdateMapping(map);
				// if (map.panel_knob_id == panel_knob_i) {
				// 	auto scaled_val = map.get_mapped_val(knobpos.value());
				// 	patch->set_or_add_static_knob_value(map.module_id, map.param_id, scaled_val);
				// }
			}

			// // Same for the MIDI Map
			// for (auto &map : patch->midi_maps.set) {
			// 	UpdateMapping(map);
			// 	pr_dbg("midi %d %f\n", map.param_id, knobpos.value());
			// 	// if (map.panel_knob_id == panel_knob_i) {
			// 	// 	auto scaled_val = map.get_mapped_val(knobpos.value());
			// 	// 	patch->set_or_add_static_knob_value(map.module_id, map.param_id, scaled_val);
			// 	// }
			// }
		}

		for (auto &map : patch->midi_maps.set) {
			auto knobpos = info.params.panel_knob_new_value(map.panel_knob_id);
			if (knobpos.has_value()) {
				auto scaled_val = map.get_mapped_val(knobpos.value());
				pr_dbg("midi %d %f -> %f\n", map.param_id, knobpos.value(), scaled_val);
				patch->set_or_add_static_knob_value(map.module_id, map.param_id, scaled_val);
			}
		}
	}

	void handle_back_event() {
		// Interpret and pass on back button events
		if (info.metaparams.meta_buttons[0].is_just_released()) {
			if (!info.metaparams.ignore_metabutton_release)
				info.metaparams.back_button.register_falling_edge();
			else
				info.metaparams.ignore_metabutton_release = false;
		}
	}

	void handle_notifications() {
		auto msg = info.notify_queue.get();
		if (msg) {
			pr_info("%s\n", msg->message.c_str());
			DisplayNotification::show(*msg);
		}
	}

	void debug_print_args(auto newpage) {
		PatchLocation nullloc{"", Volume::MaxVolumes};
		pr_trace("Args: mod: %d, panel: %d, set: %d, patchnamehash: %u\n",
				 newpage->args->module_id.value_or(88),
				 newpage->args->mappedknob_id.value_or(88),
				 newpage->args->view_knobset_id.value_or(88),
				 (unsigned)newpage->args->patch_loc_hash.value_or(nullloc).filehash);

		if (newpage->args->element_indices) {
			auto i = newpage->args->element_indices.value();
			pr_trace("Ind: %d %d %d %d\n", i.param_idx, i.input_idx, i.output_idx, i.light_idx);
		}

		if (newpage->args->element_counts) {
			auto i = newpage->args->element_counts.value();
			pr_trace("Cnt: %zu %zu %zu %zu\n", i.num_params, i.num_inputs, i.num_outputs, i.num_lights);
		}
	}
};

} // namespace MetaModule
