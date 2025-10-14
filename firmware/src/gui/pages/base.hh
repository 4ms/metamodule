#pragma once
#include "dynload/plugin_manager.hh"
#include "gui/gui_state.hh"
#include "gui/notify/queue.hh"
#include "gui/pages//file_browser/file_browser.hh"
#include "gui/pages/missing_plugin_scan.hh"
#include "gui/pages/page_args.hh"
#include "gui/pages/page_list.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "patch_file/change_checker.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings.hh"
#include "util/poll_change.hh"

// Use for helpers:

namespace MetaModule
{

struct PatchContext {
	FileStorageProxy &patch_storage;
	OpenPatchManager &open_patch_manager;
	PatchPlayLoader &patch_playloader;
	ParamsMidiState &params;
	MetaParams &metaparams;
	NotificationQueue &notify_queue;
	PatchModQueue &patch_mod_queue;
	PageList &page_list;
	GuiState &gui_state;
	UserSettings &settings;
	PluginManager &plugin_manager;
	FatFileIO &ramdisk;
	PatchFileChangeChecker &file_change_checker;
	FileBrowserDialog &file_browser;
};

struct PageBase {
	FileStorageProxy &patch_storage;
	OpenPatchManager &patches;
	PatchPlayLoader &patch_playloader;
	ParamsMidiState &params;
	MetaParams &metaparams;
	NotificationQueue &notify_queue;
	PatchModQueue &patch_mod_queue;
	PageList &page_list;
	GuiState &gui_state;
	UserSettings &settings;
	FileBrowserDialog &file_browser;

	PageArguments args;

	PatchFileChangeChecker &file_change_checker;
	PollChange file_change_poll{500};

	PageId id;

	MissingPluginScanner missing_plugins;

	static constexpr uint32_t MaxBufferWidth = 320;
	//Note: LVGL cannot deal with canvas larger than 2047 because there are only 11 bits for the height. 2047 / 180 = 11.4
	static constexpr uint32_t MaxBufferHeight = 11 * 180;

	static inline std::array<lv_color_t, MaxBufferHeight * MaxBufferWidth> page_pixel_buffer;

	lv_group_t *group = nullptr;
	lv_obj_t *screen = nullptr;

	PageBase(PatchContext info, PageId id)
		: patch_storage{info.patch_storage}
		, patches{info.open_patch_manager}
		, patch_playloader{info.patch_playloader}
		, params{info.params}
		, metaparams{info.metaparams}
		, notify_queue{info.notify_queue}
		, patch_mod_queue{info.patch_mod_queue}
		, page_list{info.page_list}
		, gui_state{info.gui_state}
		, settings{info.settings}
		, file_browser{info.file_browser}
		, file_change_checker{info.file_change_checker}
		, id{id}
		, missing_plugins{info.plugin_manager, lv_layer_sys(), settings.missing_plugins} {
		page_list.register_page(this, id);
	}

	virtual ~PageBase() = default;

	void init_bg(lv_obj_t *screen_ptr) {
		group = lv_group_create();
		screen = screen_ptr;
		lv_obj_set_size(screen, 320, 240); //TODO: use Screen Conf, not hard-set values
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_STATE_DEFAULT);
	}

	void focus(PageArguments const *args) {
		gui_state.back_button.clear_events();
		metaparams.rotary_button.clear_events();

		if (group) {
			lv_indev_set_group(lv_indev_get_next(nullptr), group);
		}

		// copy args to the PageBase instance
		if (args)
			this->args = *args;
		prepare_focus();

		if (screen)
			lv_scr_load(screen);
	}

	void load_prev_page() {
		page_list.request_last_page();
	}

	void load_page(PageId next_page, PageArguments new_args) {
		page_list.update_state(id, args);
		page_list.request_new_page(next_page, new_args);
	}

	virtual void prepare_focus() {
	}

	virtual void blur() {
	}

	virtual void update() {
	}

	bool patch_is_playing(std::optional<PatchLocHash> patch_loc_hash) {
		if (patch_loc_hash.has_value()) {
			return (patch_loc_hash.value() == patches.get_playing_patch_loc_hash());
		} else {
			return false;
		}
	}

	// Each page calls this periodically.
	// TODO: Try running this automatically, and have pages opt-out of it when ICC bus is busy or patch should not be reloaded?
	bool is_checking_missing_plugins = false;

	void poll_patch_file_changed() {

		file_change_poll.poll(get_time(), [this] {
			auto playing_patch = patches.get_playing_patch();

			if (playing_patch) {
				const auto status = file_change_checker.check_patch(patches.get_playing_patch_loc());

				if (status == PatchFileChangeChecker::Status::DidReload) {
					missing_plugins.start();
					is_checking_missing_plugins = true;
				}

				if (status == PatchFileChangeChecker::Status::FailLoadFile) {
					pr_err("Error: Failed to load playing patch file: '%s')\n",
						   patches.get_playing_patch_loc().filename.c_str());
				}
			}

			auto view_patch = patches.get_view_patch();
			if (view_patch && view_patch != playing_patch) {
				const auto status = file_change_checker.check_patch(patches.get_view_patch_loc());

				if (status == PatchFileChangeChecker::Status::DidReload) {
					notify_queue.put({"New patch file detected, refreshed", Notification::Priority::Status, 800});
					//gui_state.force_redraw_patch = true;// do we need to do this???
					gui_state.view_patch_file_changed = true;
				}

				if (status == PatchFileChangeChecker::Status::FailLoadFile) {
					pr_err("Error: File failed to auto reload\n");
				}
			}

			return false; //ignored
		});

		if (is_checking_missing_plugins) {
			missing_plugins.process(patches.get_playing_patch(), group, [this] {
				patch_playloader.request_reload_playing_patch(false);

				if (patches.get_playing_patch() == patches.get_view_patch()) {
					gui_state.force_redraw_patch = true;
					gui_state.view_patch_file_changed = true;
				}

				is_checking_missing_plugins = false;
			});
		}
	}
};
} // namespace MetaModule
