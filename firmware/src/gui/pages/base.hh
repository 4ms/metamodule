#pragma once
#include "conf/panel_conf.hh"
#include "dynload/plugin_manager.hh"
#include "gui/elements/element_name.hh"
#include "gui/notify/queue.hh"
#include "gui/pages/page_args.hh"
#include "gui/pages/page_list.hh"
#include "gui/pages/view_settings.hh"
#include "lvgl.h"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "patch_file/file_storage_proxy.hh"
#include "patch_file/open_patch_manager.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

// Use for helpers:

namespace MetaModule
{

enum class PageChangeDirection { Back, Forward, Jump };

struct GuiState {
	struct CableBeginning {
		Jack jack;
		ElementType type;
		bool has_connections;
	};
	std::optional<CableBeginning> new_cable{};

	bool force_redraw_patch{};

	std::optional<Volume> force_refresh_vol{};

	bool do_write_settings{};

};

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
	ViewSettings &settings;
	PluginManager &plugin_manager;
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
	ViewSettings &settings;

	PageArguments args;

	PageId id;

	static constexpr uint32_t MaxBufferWidth = 320 * 4;
	static constexpr uint32_t MaxBufferHeight = 240 * 4;
	static inline std::array<lv_color_t, MaxBufferHeight * MaxBufferWidth> page_pixel_buffer;

	// Why doesn't this work?
	// uint8_t *buffer = StaticBuffers::gui_scratch_buffer;
	// uint8_t *cable_buf = StaticBuffers::gui_scratch_screen;

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
		, id{id} {
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
		metaparams.back_button.clear_events();
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
		page_list.update_state(id, args);
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
