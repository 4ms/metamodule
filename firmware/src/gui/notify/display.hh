#pragma once
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/notification.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"

namespace MetaModule
{

//TODO:
// have a panel for messages, height=content.
// messages have a string, type (err/status =color? font?), and duration.
// to show a message, create a new message component (label in a panel).
// keep track of each message component's start and end time.
// animation would need to be fade in/out? Maybe slide left/right?

struct DisplayNotification {

	static void show(Notification const &msg, bool animate) {
		lv_label_set_text(ui_MessageLabel, msg.message.c_str());

		auto duration = (msg.duration_ms > 0) ? msg.duration_ms : 5000;
		if (animate) {
			slide_down_up_animation(ui_MessagePanel, duration);
		} else {
			disappear_animation(ui_MessagePanel, duration);
		}
	}

	static void flash_overload(unsigned num_overruns) {
		if (num_overruns > 0) {
			lv_show(ui_OverloadMsgLabel);
			lv_obj_set_style_opa(ui_OverloadMsgLabel, LV_OPA_100, LV_PART_MAIN);
			Flashfade_Animation(ui_OverloadMsgLabel, 0);
		}
	}

	static void slide_down_up_animation(lv_obj_t *obj, int hold_time) {
		lv_obj_refr_size(obj);
		lv_obj_refr_pos(obj);
		int offscreen_y = lv_obj_get_height(obj) * 2 + 10;

		lv_anim_t anim;
		lv_anim_init(&anim);
		lv_anim_set_time(&anim, 400);
		lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
		lv_anim_set_var(&anim, obj);
		lv_anim_set_values(&anim, -1 * offscreen_y, 0);
		lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
		lv_anim_set_delay(&anim, 0);
		lv_anim_set_playback_time(&anim, 400);
		lv_anim_set_playback_delay(&anim, hold_time + 400);
		lv_anim_set_early_apply(&anim, false);
		lv_anim_start(&anim);
	}

	static void disappear_animation(lv_obj_t *obj, int hold_time) {
		lv_obj_refr_size(obj);
		int startpos = lv_obj_get_height(obj) * 2 + 10;

		lv_anim_t anim;
		lv_anim_init(&anim);
		lv_anim_set_time(&anim, 1);
		lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
		lv_anim_set_var(&anim, obj);
		lv_anim_set_values(&anim, -1 * startpos, 0);
		lv_anim_set_path_cb(&anim, lv_anim_path_step);
		lv_anim_set_delay(&anim, 0);
		lv_anim_set_playback_time(&anim, 1);
		lv_anim_set_playback_delay(&anim, hold_time);
		lv_anim_set_early_apply(&anim, false);
		lv_anim_start(&anim);
	}
};

} // namespace MetaModule
