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

	static void show(Notification const &msg) {
		lv_label_set_text(ui_MessageLabel, msg.message.c_str());

		if (msg.duration_ms > 0) {
			slide_down_up_animation(ui_MessagePanel, msg.duration_ms);
		} else {
			slide_down_up_animation(ui_MessagePanel, 10000);
		}
	}

	static void flash_overload(unsigned num_overruns) {
		if (num_overruns > 0) {
			lv_show(ui_OverloadMsgLabel);
			lv_obj_set_style_opa(ui_OverloadMsgLabel, LV_OPA_100, LV_PART_MAIN);
			Flashfade_Animation(ui_OverloadMsgLabel, 0);
		}
	}

	static inline ui_anim_user_data_t user_data{};

	static void slide_down_up_animation(lv_obj_t *TargetObject, int hold_time) {
		user_data.target = TargetObject;
		user_data.val = -1;
		lv_anim_t anim;
		lv_anim_init(&anim);
		lv_anim_set_time(&anim, 400);
		lv_anim_set_user_data(&anim, &user_data);
		lv_anim_set_custom_exec_cb(&anim, _ui_anim_callback_set_y);
		lv_anim_set_values(&anim, -240, 0);
		lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
		lv_anim_set_delay(&anim, 0);
		// lv_anim_set_deleted_cb(&anim, _ui_anim_callback_free_user_data);
		lv_anim_set_playback_time(&anim, 400);
		lv_anim_set_playback_delay(&anim, hold_time + 400);
		lv_anim_set_repeat_count(&anim, 0);
		lv_anim_set_repeat_delay(&anim, 0);
		lv_anim_set_early_apply(&anim, false);
		lv_anim_start(&anim);
	}
};

} // namespace MetaModule
