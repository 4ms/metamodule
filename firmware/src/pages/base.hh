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
	lv_obj_t *screen;

	PageBase(PatchInfo info)
		: patch_list{info.patch_list}
		, patch_player{info.patch_player}
		, params{info.params}
		, metaparams{info.metaparams}
		, mbox{info.mbox}
	{}

	virtual ~PageBase() = default;
	virtual void init() {}

	void init_bg()
	{
		lv_obj_set_size(screen, LV_HOR_RES_MAX, LV_VER_RES_MAX);
		lv_obj_set_style_local_bg_color(screen, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x000000));
	}

	virtual void focus(PageChangeDirection dir)
	{
		auto animation_style = dir == PageChangeDirection::Back	   ? LV_SCR_LOAD_ANIM_MOVE_LEFT :
							   dir == PageChangeDirection::Forward ? LV_SCR_LOAD_ANIM_MOVE_RIGHT :
																	   LV_SCR_LOAD_ANIM_FADE_ON;
		lv_scr_load_anim(screen, animation_style, 500, 0, false);
	}

	virtual void blur() {}

	virtual void update() {}
};
} // namespace MetaModule
