#pragma once

#include "../easiglib/util.hh"

struct Switches : Nocopy {

	Switches() {
		for (int i = 0; i < 16; i++)
			Debounce();
	}

	enum Switch { SCALE, MOD, TWIST, WARP };
	enum State { UP = 1, DOWN = 2, MID = 3 };

	struct ThreePosSwitch {
		State state_ = MID;
		State last_state_ = MID;

		void Debounce() {
			last_state_ = state_;
		}

		// Always called after Switches::Debounce():
		bool just_switched_mid() {
			return state_ == MID && last_state_ != MID;
		}
		bool just_switched_up() {
			return state_ == UP && last_state_ != UP;
		}
		bool just_switched_down() {
			return state_ == DOWN && last_state_ != DOWN;
		}

		State get() {
			//We don't want to call Debounce() here, right? It'll mess up just_switched_*():
			//Debounce();
			return state_;
		}

		void set(State s) {
			last_state_ = state_;
			state_ = s;
		}
	};

	ThreePosSwitch scale_, mod_, twist_, warp_;

	void Debounce() {
		scale_.Debounce();
		mod_.Debounce();
		twist_.Debounce();
		warp_.Debounce();
	}
};
