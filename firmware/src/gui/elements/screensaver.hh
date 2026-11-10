#pragma once

#include "gui/helpers/lv_helpers.hh"
#include "gui/slsexport/meta5/ui.h"
#include "pr_dbg.hh"
#include "src/core/lv_disp.h"
#include "user_settings/screensaver_settings.hh"
#include <array>
#include <utility>

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

	// How long the selected display is shown before the screen goes black
	static constexpr uint64_t MaxSelectedDisplayMs = 3 * 60 * 60 * 1000;

	// Blank: the black overlay. Display: a module display is shown full-screen (by the PageManager)
	enum class Mode { Off, Blank, Display };

	bool is_active() const {
		return mode != Mode::Off;
	}

	bool in_display_mode() const {
		return mode == Mode::Display;
	}

	bool can_wake_on_knob() const {
		return s.knobs_can_wake;
	}

	void wake() {
		lv_disp_trig_activity(nullptr);
		lv_hide(screensaver);
		if (mode == Mode::Display)
			display_woke = true;
		mode = Mode::Off;
	}

	bool timed_out() const {
		return lv_disp_get_inactive_time(nullptr) >= s.timeout_ms;
	}

	// The selected display has been shown long enough that a still part of it could burn into the screen
	bool display_timed_out() const {
		return uint64_t{lv_disp_get_inactive_time(nullptr)} >= uint64_t{s.timeout_ms} + MaxSelectedDisplayMs;
	}

	void show_blank() {
		mode = Mode::Blank;
		lv_obj_move_foreground(screensaver);
		lv_show(screensaver);
	}

	void enter_display_mode() {
		lv_hide(screensaver);
		mode = Mode::Display;
	}

	// The display is no longer shown for some other reason (e.g. the patch was unloaded)
	void reset_display_mode() {
		if (mode == Mode::Display)
			mode = Mode::Off;
	}

	// Returns true once after the display screensaver was woken
	bool take_display_wake() {
		return std::exchange(display_woke, false);
	}

private:
	Mode mode = Mode::Off;
	bool display_woke = false;
};
} // namespace MetaModule
