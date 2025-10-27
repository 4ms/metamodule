#pragma once
#include "console/pr_dbg.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/notification.hh"
#include "gui/slsexport/meta5/ui.h"
#include "lvgl.h"
#include <string_view>

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

		if (lv_obj_get_y(ui_MessagePanel) <= -30) {
			SlideDown_Animation(ui_MessagePanel, 0);
		}
		if (msg.duration_ms > 0)
			SlideUp_Animation(ui_MessagePanel, msg.duration_ms);
	}

	static void flash_overload(unsigned num_overruns) {
		if (num_overruns > 0) {
			lv_show(ui_OverloadMsgLabel);
			lv_obj_set_style_opa(ui_OverloadMsgLabel, LV_OPA_100, LV_PART_MAIN);
			Flashfade_Animation(ui_OverloadMsgLabel, 0);
		}
	}
};

} // namespace MetaModule
