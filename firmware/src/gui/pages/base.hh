#pragma once
#include "conf/panel_conf.hh"
#include "gui/message_queue.hh"
#include "lvgl.h"
#include "params.hh"
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
	Params &params;
	MetaParams &metaparams;
	MessageQueue &msg_queue;
	PatchModQueue &patch_mod_queue;
};

struct PageBase {
	PatchStorageProxy &patch_storage;
	PatchPlayLoader &patch_playloader;
	Params &params;
	MetaParams &metaparams;
	MessageQueue &msg_queue;
	PatchModQueue &patch_mod_queue;

	static constexpr uint32_t MaxBufferWidth = 320 * 4;
	static constexpr uint32_t MaxBufferHeight = 240 * 4;
	static inline std::array<lv_color_t, MaxBufferHeight * MaxBufferWidth> page_pixel_buffer;

	static inline std::array<uint8_t, LV_CANVAS_BUF_SIZE_TRUE_COLOR_ALPHA(320, 240)> cable_buf;
	// Why doesn't this work?
	// uint8_t *buffer = StaticBuffers::gui_scratch_buffer;
	// uint8_t *cable_buf = StaticBuffers::gui_scratch_screen;

	lv_group_t *group = nullptr;
	lv_obj_t *screen = nullptr;

	PageBase(PatchInfo info)
		: patch_storage{info.patch_storage}
		, patch_playloader{info.patch_playloader}
		, params{info.params}
		, metaparams{info.metaparams}
		, msg_queue{info.msg_queue}
		, patch_mod_queue{info.patch_mod_queue} {
	}

	virtual ~PageBase() = default;
	virtual void init() {
	}

	void init_bg(lv_obj_t *screen_ptr) {
		group = lv_group_create();
		screen = screen_ptr;
		lv_obj_set_size(screen, 320, 240); //TODO: use Screen Conf, not hard-set values
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_STATE_DEFAULT);
	}

	void focus() {

		for (auto &b : metaparams.meta_buttons)
			b.clear_events();

		metaparams.rotary_button.clear_events();

		if (group) {
			// From LVGL v8.1 docs: "An input device can send the keys to only one group"
			// Therefore we must re-associate the indev (rotary) with the page's group
			// whenever the page changes
			lv_indev_set_group(lv_indev_get_next(nullptr), group);
			lv_group_set_editing(group, true);
		}

		// Animation:
		// auto animation_style = LV_SCR_LOAD_ANIM_FADE_ON;
		// lv_scr_load_anim(screen, animation_style, 200, 0, false);

		prepare_focus();

		if (screen)
			lv_scr_load(screen);
	}

	virtual void prepare_focus() {
	}

	virtual void blur() {
	}

	virtual void update() {
	}

	//TODO: add helpers? or add to separate class/namespace?
	// std::string_view read_slug() {
	// 	auto module_id = PageList::get_selected_module_id();
	// 	auto patch_id = PageList::get_selected_patch_id();
	// 	const PatchData &patch = patch_list.get_patch(patch_id);
	// 	if (patch.patch_name.length() == 0)
	// 		return "";
	// 	if (module_id >= patch.module_slugs.size())
	// 		return "";

	// 	return patch.module_slugs[module_id];
	// }
};
} // namespace MetaModule
