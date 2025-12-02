#pragma once
#include "util/debouncer.hh"
#include <cmath>

namespace MetaModule
{

// A catch-all of data shared between cores
struct MetaParams {
	Toggler low_sel{};
	Toggler mid_sel{};
	Toggler high_sel{};

	unsigned eq_switch{};
	unsigned comp_switch{};

	bool inL_plugged{};
	bool inR_plugged{};
	bool outL_plugged{};
	bool outR_plugged{};
	bool cv_plugged{};

	void clear() {
		*this = MetaParams{};
	}

	// For rotary motion: adds events in `that` to events in `this`, leaving `that` untouched
	// Copies non-event signals (CV, audio)
	// Used with write_sync()
	void update_with(MetaParams &that) {
		low_sel.transfer_events(that.low_sel);
		mid_sel.transfer_events(that.mid_sel);
		high_sel.transfer_events(that.high_sel);
		eq_switch = that.eq_switch;
		comp_switch = that.comp_switch;
		inL_plugged = that.inL_plugged;
		inR_plugged = that.inR_plugged;
		outL_plugged = that.outL_plugged;
		outR_plugged = that.outR_plugged;
		cv_plugged = that.cv_plugged;
	}

	// Moves rotary motion events from `that` to `this` (removing them from `that`,
	// and adding them to existing events in `this`)
	// Copies non-event signals (CV, audio)
	// Used with read_sync()
	void transfer(MetaParams &that) {
		update_with(that);
	}
};

} // namespace MetaModule
