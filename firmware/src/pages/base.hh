#pragma once
#include "conf/panel_conf.hh"
#include "lvgl/lvgl.h"
#include "params.hh"
#include "patch_player.hh"
#include "patchlist.hh"
#include "util/geometry.hh"
//LVGL:
#include "pages/gui-guider/gui_guider.h"

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

	static inline lv_ui base_ui{};
	static inline lv_ui *ui = &base_ui;
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
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_INDICATOR | LV_STATE_FOCUSED);
	}

	virtual void focus(PageChangeDirection dir) {
		if (group) {
			lv_indev_set_group(lv_indev_get_next(nullptr), group);
			lv_group_set_editing(group, true);
		}

		// auto animation_style = dir == PageChangeDirection::Back	   ? LV_SCR_LOAD_ANIM_MOVE_RIGHT :
		// 					   dir == PageChangeDirection::Forward ? LV_SCR_LOAD_ANIM_MOVE_LEFT :
		// 															   LV_SCR_LOAD_ANIM_FADE_ON;
		// auto animation_style = LV_SCR_LOAD_ANIM_FADE_ON;
		// lv_scr_load_anim(screen, animation_style, 200, 0, false);
		lv_scr_load(screen);
	}

	virtual void blur() {
	}

	virtual void update() {
	}
};
} // namespace MetaModule
