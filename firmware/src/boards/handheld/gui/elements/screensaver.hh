#pragma once
#include "user_settings/screensaver_settings.hh"

namespace MetaModule
{

class Screensaver {
	bool active = false;
	ScreensaverSettings &s;

public:
	Screensaver(ScreensaverSettings &s)
		: s{s} {

		wake();
	}

	bool is_active() const {
		return active;
	}

	bool can_wake_on_knob() const {
		return s.knobs_can_wake;
	}

	void wake() {
		active = false;
	}

	void update() {
		if (active)
			return;

		//TODO: if timeout, active = true
	}
};
} // namespace MetaModule
