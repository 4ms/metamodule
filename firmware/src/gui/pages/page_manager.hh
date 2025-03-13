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
#include "vcv_plugin/internal/osdialog-mm.hh"

namespace MetaModule
{

class PageManager {
	SlsComponentInit sls_comp_init;

	PatchFileChangeChecker file_change_checker;

	PatchContext info;
	PageList page_list;
	GuiState gui_state;
	ButtonLight button_light;
	Screensaver &screensaver;

	PatchSelectorSubdirPanel subdir_panel;
	FileBrowserDialog file_browser;
	FileSaveDialog file_save_dialog{info.patch_storage, subdir_panel};

	MainMenuPage page_mainmenu{info};
	PatchSelectorPage page_patchsel{info, subdir_panel};
	PatchViewPage page_patchview{info, file_save_dialog};
	ModuleViewPage page_module{info};
	KnobSetViewPage page_knobsetview{info};
	KnobMapPage page_knobmap{info};
	SystemMenuPage page_systemmenu{info};
	ModuleListPage page_modulelist{info};
	JackMapViewPage page_jackmap{info};

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
				Screensaver &screensaver,
				FatFileIO &ramdisk)
		: file_change_checker{patch_storage,
							  open_patch_manager,
							  patch_playloader,
							  gui_state,
							  notify_queue,
							  settings.filesystem}
		, info{.patch_storage = patch_storage,
			   .open_patch_manager = open_patch_manager,
			   .patch_playloader = patch_playloader,
			   .params = params,
			   .metaparams = metaparams,
			   .notify_queue = notify_queue,
			   .patch_mod_queue = patch_mod_queue,
			   .page_list = page_list,
			   .gui_state = gui_state,
			   .settings = settings,
			   .plugin_manager = plugin_manager,
			   .ramdisk = ramdisk,
			   .file_change_checker = file_change_checker,
			   .file_browser = file_browser}
		, screensaver{screensaver}
		, file_browser{patch_storage, notify_queue} {

		// Register file browser with VCV to support osdialog/async_dialog_filebrowser
		register_file_browser_vcv(file_browser, file_save_dialog);
	}

	void init() {
		page_list.request_initial_page(PageId::MainMenu, {});
		button_light.display_knobset(0);
	}

	void update_current_page() {

		handle_knobset_change();

		update_screensaver();

		handle_back_event();

		if (auto newpage = page_list.get_requested_page()) {
			if (newpage->page) {
				cur_page->blur();
				cur_page = newpage->page;
				// debug_print_args(newpage);
				cur_page->focus(newpage->args);
			}
		} else {
			if (file_browser.is_visible()) {
				if (gui_state.back_button.is_just_released())
					file_browser.back_event();
				file_browser.update();

				gui_state.file_browser_visible.register_state(true);

			} else if (file_save_dialog.is_visible()) {
				if (gui_state.back_button.is_just_released())
					file_save_dialog.back_event();

				file_save_dialog.update();

				gui_state.file_browser_visible.register_state(true);

			} else {
				gui_state.file_browser_visible.register_state(false);

				cur_page->update();

				// Don't let old events do surprising things when you change pages
				gui_state.file_browser_visible.clear_events();
			}
		}

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
							{"Using Knob Set \"" + ks_name + "\"", Notification::Priority::Status, 600});

					button_light.display_knobset(next_knobset);
				}
			}
		}

		if (button_light.display_knobset() != info.page_list.get_active_knobset()) {
			button_light.display_knobset(info.page_list.get_active_knobset());
		}
	}

	void update_screensaver() {
		// Wake screen saver on knob movement
		if (screensaver.is_active() && screensaver.can_wake_on_knob()) {
			for (auto const &knob : info.params.knobs) {
				if (knob.changed) {
					screensaver.wake();
					break;
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

		DisplayNotification::flash_overload(info.metaparams.audio_overruns);
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
