#pragma once

#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "pr_dbg.hh"
#include "screensaver_settings.hh"
#include "src/core/lv_disp.h"
#include <array>

namespace MetaModule
{

class Screensaver {
	lv_obj_t *screensaver;
	ScreensaverSettings &s;

public:
	Screensaver(ScreensaverSettings &s)
		: screensaver(lv_obj_create(lv_layer_sys()))
		, s{s} {

		lv_obj_set_size(screensaver, lv_pct(100), lv_pct(100));

		lv_obj_set_width(screensaver, lv_pct(100));
		lv_obj_set_height(screensaver, lv_pct(100));
		lv_obj_set_align(screensaver, LV_ALIGN_CENTER);
		lv_obj_set_style_bg_color(screensaver, lv_color_hex(0x000000), LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(screensaver, lv_color_hex(0x000000), LV_STATE_DEFAULT);
		lv_obj_set_style_radius(screensaver, 0, LV_STATE_DEFAULT);
		wake();
	}

	bool is_active() const {
		return !lv_obj_has_flag(screensaver, LV_OBJ_FLAG_HIDDEN);
	}
	// return false if event is consumed
	void wake() {
		lv_disp_trig_activity(nullptr);
		lv_hide(screensaver);
	}

	void wake_knob() {
		if (!s.knobs_can_wake)
			return;
		return static_cast<void>(wake());
	}

	void update() {
		if (lv_obj_is_visible(screensaver))
			return;

		const auto t = lv_disp_get_inactive_time(nullptr);

		if (t < s.timeout_ms)
			return;

		lv_obj_move_foreground(screensaver);
		lv_show(screensaver);
	}
};
} // namespace MetaModule
