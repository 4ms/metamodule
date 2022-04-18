#pragma once
#include "conf/panel_conf.hh"
#include "lvgl/lvgl.h"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "util/geometry.hh"
#include <optional>

namespace MetaModule
{

enum class PageChangeDirection { Back, Forward, Jump };

struct PatchInfo {
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	MetaParams &metaparams;
	UiAudioMailbox &mbox;
};

struct PageBase {
	PatchList &patch_list;
	PatchPlayer &patch_player;
	Params &params;
	MetaParams &metaparams;
	UiAudioMailbox &mbox;

	lv_group_t *group = nullptr;
	lv_obj_t *screen = nullptr;

	PageBase(PatchInfo info)
		: patch_list{info.patch_list}
		, patch_player{info.patch_player}
		, params{info.params}
		, metaparams{info.metaparams}
		, mbox{info.mbox} {
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

		lv_scr_load(screen);
	}

	virtual void prepare_focus() {
	}

	virtual void blur() {
	}

	virtual void update() {
	}
};
} // namespace MetaModule
