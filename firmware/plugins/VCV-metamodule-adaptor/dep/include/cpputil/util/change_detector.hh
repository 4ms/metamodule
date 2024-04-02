#pragma once

// Can be used when update() is called any number of times
// changed() will always return true if there ever was at least one change of state
// since the last call to changed()
struct ChangeDetector {
	bool last_state_ = false;
	bool changed_ = false;

	void update(bool state) {
		if (last_state_ != state) {
			changed_ = true;
			last_state_ = state;
		}
	}

	bool changed() {
		if (changed_) {
			changed_ = false;
			return true;
		}
		return false;
	}
};
