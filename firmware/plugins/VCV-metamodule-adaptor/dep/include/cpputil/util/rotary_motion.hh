#pragma once
#include <cstdint>

struct RotaryMotion {
	int32_t abs_pos = 0;
	int32_t motion = 0;

	// Read the motion and clear it
	int32_t use_motion() {
		auto tmp = motion;
		motion = 0;
		return tmp;
	}

	// Add motion to this
	void add_motion(const RotaryMotion &that) {
		motion += that.motion;
		abs_pos += that.motion;
	}

	// Move motion from that to this
	void transfer_motion(RotaryMotion &that) {
		auto that_motion = that.use_motion();
		motion += that_motion;
		abs_pos += that_motion;
	}
};
