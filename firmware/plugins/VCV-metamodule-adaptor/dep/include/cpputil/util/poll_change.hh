#pragma once

// Detects if any change of state has occurred
// But only checks at regular periods of `update_ticks`
class PollChange {
public:
	PollChange(int update_ticks)
		: update_ticks{update_ticks} {
	}

	void reset() {
		change_detected = true;
	}

	void poll(int now, bool state) {
		if (now - last_update_time >= update_ticks) {
			last_update_time = now;

			if (current_state != state) {
				current_state = state;
				change_detected = true;
			}
		}
	}

	// Defer calling state_func() until poll time has expired.
	// Useful if checking the state is a heavy operation.
	void poll(int now, auto state_func) {
		if (now - last_update_time >= update_ticks) {
			last_update_time = now;

			bool state = state_func();
			if (current_state != state) {
				current_state = state;
				change_detected = true;
			}
		}
	}

	bool take_change() {
		if (change_detected) {
			change_detected = false;
			return true;
		}
		return false;
	}

private:
	bool current_state;
	bool change_detected = false;
	int last_update_time = 0;
	int update_ticks;
};
