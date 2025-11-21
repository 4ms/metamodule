#pragma once
#include "dynload/plugin_manager.hh"
#include "gui/gui_state.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_args.hh"
#include "gui/pages/page_list.hh"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_play/patch_playloader.hh"
#include "user_settings/settings.hh"

namespace MetaModule
{

struct PatchContext {
	FileStorageProxy &patch_storage;
	OpenPatchManager &open_patch_manager;
	PatchPlayLoader &patch_playloader;
	ParamsState &params;
	MetaParams &metaparams;
	NotificationQueue &notify_queue;
	PageList &page_list;
	GuiState &gui_state;
	UserSettings &settings;
	PluginManager &plugin_manager;
	FatFileIO &ramdisk;
};

struct PageBase {
	FileStorageProxy &patch_storage;
	OpenPatchManager &patches;
	PatchPlayLoader &patch_playloader;
	ParamsState &params;
	MetaParams &metaparams;
	NotificationQueue &notify_queue;
	PageList &page_list;
	GuiState &gui_state;
	UserSettings &settings;

	PageArguments args;

	PageId id;

	PageBase(PatchContext info, PageId id)
		: patch_storage{info.patch_storage}
		, patches{info.open_patch_manager}
		, patch_playloader{info.patch_playloader}
		, params{info.params}
		, metaparams{info.metaparams}
		, notify_queue{info.notify_queue}
		, page_list{info.page_list}
		, gui_state{info.gui_state}
		, settings{info.settings}
		, id{id} {
		page_list.register_page(this, id);
	}

	virtual ~PageBase() = default;

	void init_bg() {
	}

	void focus(PageArguments const *args) {
		gui_state.back_button.clear_events();

		// copy args to the PageBase instance
		if (args)
			this->args = *args;
		prepare_focus();
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
};
} // namespace MetaModule
