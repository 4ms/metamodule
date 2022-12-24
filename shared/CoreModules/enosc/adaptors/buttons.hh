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
		uint8_t history_ = 0xFF;
		bool state_ = false;

		void Debounce() {
			history_ = (history_ << 1) | (**this).get();
		}
		bool just_released() const {
			return history_ == 0b01111111;
		}
		bool just_pushed() const {
			return history_ == 0b10000000;
		}
		bool pushed() const {
			return history_ == 0b00000000;
		}
		bool get() const {
			return state_;
		}
		void set(bool s) {
			state_ = !s;
		}
	};

	struct Learn : Debouncer<Learn> {
	} learn_;

	struct Freeze : Debouncer<Freeze> {
	} freeze_;

	void Debounce() {
		learn_.Debounce();
		freeze_.Debounce();
	}
};
