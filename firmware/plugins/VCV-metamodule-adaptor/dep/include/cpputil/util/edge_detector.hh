#pragma once

struct EdgeStateDetector {
	bool state_ = false;
	bool last_state_ = false;

	void update(bool state) {
		last_state_ = state_;
		state_ = state;
	}

	bool changed() const {
		return last_state_ != state_;
	}

	bool went_high() const {
		return (!last_state_ && state_);
	}

	bool went_low() const {
		return (last_state_ && !state_);
	}

	bool is_high() const {
		return state_;
	}

	bool staying_high() const {
		return (last_state_ && state_);
	}

	bool staying_low() const {
		return (!last_state_ && !state_);
	}

	void reset() {
		state_ = false;
		last_state_ = false;
	}
};
