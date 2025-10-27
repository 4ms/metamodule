#pragma once
#include "console/pr_dbg.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/notify/notification.hh"
#include "lvgl.h"
#include <string_view>

namespace MetaModule
{

struct DisplayNotification {

	static void show(Notification const &msg) {
		//TODO
	}

	static void flash_overload(unsigned num_overruns) {
		//TODO
	}
};

} // namespace MetaModule
