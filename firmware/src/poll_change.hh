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

	void poll(int now, bool current_state) {
		if (now - last_update_time >= update_ticks) {
			last_update_time = now;

			if (state != current_state) {
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
	bool state;
	bool change_detected = false;
	int last_update_time = 0;
	int update_ticks;
};
