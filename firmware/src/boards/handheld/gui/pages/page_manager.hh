#pragma once
#include "gui/elements/screensaver.hh"
#include "gui/notify/display.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/base.hh"
#include "gui/pages/status_bar.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings_file.hh"

#include "gui/pages/fullscreen_graphic.hh"
// #include "gui/pages/main_menu.hh"

namespace MetaModule
{

class PageManager {
	PatchContext info;
	PageList page_list;
	GuiState gui_state;
	Screensaver &screensaver;
	StatusBar statusbar;

	// MainMenuPage page_mainmenu{info};
	FullscreenGraphicPage page_fullscreen_graphic;

public:
	PageBase *cur_page = &page_fullscreen_graphic;

	PageManager(FileStorageProxy &patch_storage,
				OpenPatchManager &open_patch_manager,
				PatchPlayLoader &patch_playloader,
				ParamsState &params,
				MetaParams &metaparams,
				NotificationQueue &notify_queue,
				PatchModQueue &patch_mod_queue,
				PluginManager &plugin_manager,
				UserSettings &settings,
				Screensaver &screensaver,
				FatFileIO &ramdisk)
		: info{.patch_storage = patch_storage,
			   .open_patch_manager = open_patch_manager,
			   .patch_playloader = patch_playloader,
			   .params = params,
			   .metaparams = metaparams,
			   .notify_queue = notify_queue,
			   .page_list = page_list,
			   .gui_state = gui_state,
			   .settings = settings,
			   .plugin_manager = plugin_manager,
			   .ramdisk = ramdisk}
		, screensaver{screensaver}
		, page_fullscreen_graphic{info} {
	}

	void init() {
		PageArguments args;

		args.module_id = 1;

		page_list.request_initial_page(PageId::FullscreenGraphic, args);
		statusbar.show();

		Debug::Pin2 init;
	}

	void update_current_page() {

		handle_knobset_change();

		if (auto newpage = page_list.get_requested_page()) {
			if (newpage->page) {
				cur_page->blur();
				cur_page = newpage->page;
				// debug_print_args(newpage);
				cur_page->focus(newpage->args);
			}
		} else {
			cur_page->update();
		}

		statusbar.show_battery(info.metaparams.battery_status);

		handle_audio_errors();

		handle_notifications();

		handle_write_settings();

		screensaver.update();
	}

	void handle_knobset_change() {
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
