#pragma once
#include "conf/panel_conf.hh"
#include "gui/message_queue.hh"
#include "gui/pages/page_args.hh"
#include "gui/pages/page_list.hh"
#include "lvgl.h"
#include "params/metaparams.hh"
#include "params/params_state.hh"
#include "patch_file/patch_storage_proxy.hh"
#include "patch_play/patch_mod_queue.hh"
#include "patch_play/patch_playloader.hh"

// Use for helpers:

namespace MetaModule
{

enum class PageChangeDirection { Back, Forward, Jump };

struct PatchInfo {
	PatchStorageProxy &patch_storage;
	PatchPlayLoader &patch_playloader;
	ParamsMidiState &params;
	MetaParams &metaparams;
	MessageQueue &msg_queue;
	PatchModQueue &patch_mod_queue;
	PageList &page_list;
};

struct PageBase {
	PatchStorageProxy &patch_storage;
	PatchPlayLoader &patch_playloader;
	ParamsMidiState &params;
	MetaParams &metaparams;
	MessageQueue &msg_queue;
	PatchModQueue &patch_mod_queue;
	PageList &page_list;

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

	PageBase(PatchInfo info, PageId id)
		: patch_storage{info.patch_storage}
		, patch_playloader{info.patch_playloader}
		, params{info.params}
		, metaparams{info.metaparams}
		, msg_queue{info.msg_queue}
		, patch_mod_queue{info.patch_mod_queue}
		, page_list{info.page_list}
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
		for (auto &b : metaparams.meta_buttons)
			b.clear_events();

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
		page_list.stash_state(id, args);
		page_list.request_last_page();
	}

	void load_page(PageId next_page, PageArguments new_args) {
		page_list.stash_state(id, args);
		page_list.request_new_page(next_page, new_args);
	}

	virtual void prepare_focus() {
	}

	virtual void blur() {
	}

	virtual void update() {
	}
};
} // namespace MetaModule
