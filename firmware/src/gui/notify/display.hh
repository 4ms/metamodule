#pragma once
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
		SlideDown_Animation(ui_MessagePanel, 0);
		if (msg.duration_ms > 0)
			SlideUp_Animation(ui_MessagePanel, msg.duration_ms);
	}
};

} // namespace MetaModule
