#pragma once

#include "../easiglib/util.hh"

enum Button {
	BUTTON_LEARN,
	BUTTON_FREEZE,
};

struct Buttons : Nocopy {

	Buttons() {
		for (int i = 16; i--;) {
			Debounce();
		}
	}

	template<class T>
	struct Debouncer : crtp<T, Debouncer<T>> {
		uint8_t state_ = 0xFF;
		void Debounce() {
			state_ = (state_ << 1) | (**this).get();
		}
		bool just_released() const {
			return state_ == 0b01111111;
		}
		bool just_pushed() const {
			return state_ == 0b10000000;
		}
		bool pushed() const {
			return state_ == 0b00000000;
		}
	};

	struct Learn : public Debouncer<Learn> {
		Learn();
		bool get();
	} learn_;

	struct Freeze : Debouncer<Freeze> {
		Freeze();
		bool get();
	} freeze_;

	void Debounce() {
		learn_.Debounce();
		freeze_.Debounce();
	}
};
