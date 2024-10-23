#pragma once
#include "gui/elements/screensaver.hh"
#include "gui/knobset_button.hh"
#include "gui/notify/display.hh"
#include "gui/notify/queue.hh"
#include "gui/slsexport/comp_init.hh"
#include "metaparams.hh"
#include "params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings_file.hh"

#include "gui/pages/jackmaps.hh"
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
	ButtonLight button_light;
	Screensaver &screensaver;

	MainMenuPage page_mainmenu{info};
	PatchSelectorPage page_patchsel{info, subdir_panel};
	PatchViewPage page_patchview{info, subdir_panel};
	ModuleViewPage page_module{info};
	KnobSetViewPage page_knobsetview{info};
	KnobMapPage page_knobmap{info};
	SystemMenuPage page_systemmenu{info};
	ModuleListPage page_modulelist{info};
	JackMapViewPage page_jackmap{info};

	PatchSelectorSubdirPanel subdir_panel;

public:
	PageBase *cur_page = &page_mainmenu;

	PageManager(FileStorageProxy &patch_storage,
				OpenPatchManager &open_patch_manager,
				PatchPlayLoader &patch_playloader,
				ParamsMidiState &params,
				MetaParams &metaparams,
				NotificationQueue &notify_queue,
				PatchModQueue &patch_mod_queue,
				PluginManager &plugin_manager,
				UserSettings &settings,
				Screensaver &screensaver)
		: info{patch_storage,
			   open_patch_manager,
			   patch_playloader,
			   params,
			   metaparams,
			   notify_queue,
			   patch_mod_queue,
			   page_list,
			   gui_state,
			   settings,
			   plugin_manager}
		, screensaver{screensaver} {
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

		handle_audio_errors();

		handle_notifications();

		handle_write_settings();

		screensaver.update();
	}

	void handle_knobset_change() {
		if (auto knobset_change = info.metaparams.rotary_with_metabutton.use_motion(); knobset_change != 0) {
			if (auto patch = info.open_patch_manager.get_playing_patch(); patch != nullptr) {

				if (int num_knobsets = patch->knob_sets.size(); num_knobsets > 0) {
					int cur_knobset = info.page_list.get_active_knobset();
					int next_knobset = MathTools::wrap<int>(knobset_change + cur_knobset, 0, num_knobsets - 1);

					info.patch_mod_queue.put(ChangeKnobSet{.knobset_num = (unsigned)next_knobset});
					info.page_list.set_active_knobset(next_knobset);
					std::string ks_name = patch->valid_knob_set_name(next_knobset);

					if (cur_page != page_list.page(PageId::KnobSetView))
						info.notify_queue.put(
							{"Using Knob Set \"" + ks_name + "\"", Notification::Priority::Status, 1000});

					button_light.display_knobset(next_knobset);
				}
			}
		}

		if (button_light.display_knobset() != info.page_list.get_active_knobset()) {
			button_light.display_knobset(info.page_list.get_active_knobset());
		}
	}

	// Update internal copy of patch with knob changes
	// This is used to keep GUI in sync with patch player's copy of the patch without concurrancy issues
	void update_patch_params() {
		auto patch = info.open_patch_manager.get_playing_patch();
		if (!patch)
			return;

		auto active_knobset = info.page_list.get_active_knobset();
		if (active_knobset >= patch->knob_sets.size())
			return;

		if (page_module.is_creating_map())
			return;

		// Iterate all panel knobs
		for (auto panel_knob_i = 0u; panel_knob_i < info.params.knobs.size(); panel_knob_i++) {

			// Find knobs that have moved
			auto knobpos = info.params.panel_knob_new_value(panel_knob_i);
			if (!knobpos.has_value())
				continue;

			screensaver.wake_knob();

			// Update patch for any map that's mapped to the knob that moved
			for (auto &map : patch->knob_sets[active_knobset].set) {
				if (map.panel_knob_id == panel_knob_i) {
					auto scaled_val = map.get_mapped_val(knobpos.value());
					patch->set_or_add_static_knob_value(map.module_id, map.param_id, scaled_val);
				}
			}
		}

		for (auto &map : patch->midi_maps.set) {
			auto knobpos = info.params.panel_knob_new_value(map.panel_knob_id);
			if (knobpos.has_value()) {
				// Update all MIDI maps to this CC
				for (auto &other_map : patch->midi_maps.set) {
					if (other_map.panel_knob_id == map.panel_knob_id) {
						auto scaled_val = other_map.get_mapped_val(knobpos.value());
						patch->set_or_add_static_knob_value(other_map.module_id, other_map.param_id, scaled_val);
					}
				}
			}
		}
	}

	void handle_back_event() {
		// Interpret and pass on back button events
		if (info.metaparams.meta_buttons[0].is_just_released()) {
			if (!screensaver.is_active()) {
				if (!info.metaparams.ignore_metabutton_release)
					gui_state.back_button.register_falling_edge();
				else
					info.metaparams.ignore_metabutton_release = false;
			}
			screensaver.wake();
		}
	}

	void handle_notifications() {
		auto msg = info.notify_queue.get();
		if (msg) {
			screensaver.wake();
			pr_info("Notify: %s\n", msg->message.c_str());
			DisplayNotification::show(*msg);
		}
	}

	void handle_audio_errors() {
		if (info.patch_playloader.did_audio_overrun()) {
			info.notify_queue.put({"Audio stopped: patch load > 99%.", Notification::Priority::Error, 1000});
			info.patch_playloader.clear_audio_overrun();
		}
	}

	void handle_write_settings() {
		if (gui_state.do_write_settings) {
			if (!Settings::write_settings(info.patch_storage, info.settings)) {
				pr_err("Failed to write settings file\n");
			} else
				pr_info("Wrote settings\n");

			gui_state.do_write_settings = false;
			gui_state.write_settings_after_ms = 0;
		}

		if (gui_state.write_settings_after_ms > 0) {
			if (get_time() >= gui_state.write_settings_after_ms) {

				if (!Settings::write_settings(info.patch_storage, info.settings)) {
					pr_err("Failed to write settings file (timer)\n");
				} else {
					pr_info("Wrote settings (timer)\n");
				}

				gui_state.write_settings_after_ms = 0;
			}
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
