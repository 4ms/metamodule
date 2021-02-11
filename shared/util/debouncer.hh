#pragma once
#include <cstdint>

struct Button {
	Button()
		: is_high_{false}
		, got_rising_edge_{false}
		, got_falling_edge_{false}
	{}

	bool is_high() const
	{
		return is_high_;
	}
	bool is_pressed() const
	{
		return is_high_;
	}

	bool is_just_pressed()
	{
		if (got_rising_edge_) {
			got_rising_edge_ = false;
			return true;
		} else
			return false;
	}
	bool just_went_high()
	{
		return is_just_pressed();
	}

	bool is_just_released()
	{
		if (got_falling_edge_) {
			got_falling_edge_ = false;
			return true;
		} else
			return false;
	}
	bool just_went_low()
	{
		return is_just_released();
	}

	void register_rising_edge()
	{
		is_high_ = true;
		got_rising_edge_ = true;
		got_falling_edge_ = false;
	}
	void register_falling_edge()
	{
		is_high_ = false;
		got_falling_edge_ = true;
		got_rising_edge_ = false;
	}

protected:
	bool is_high_;
	bool got_rising_edge_;
	bool got_falling_edge_;
};

template<unsigned RisingEdgePattern = 0x0000000F, unsigned FallingEdgePattern = 0xFFFFFFF0>
struct Debouncer : Button {
	Debouncer()
		: debounce_state_{0}
	{}

	void register_state(unsigned new_state)
	{
		debounce_state_ = (debounce_state_ << 1) | new_state;
		if (debounce_state_ == RisingEdgePattern) {
			register_rising_edge();
		} else if (debounce_state_ == FallingEdgePattern) {
			register_falling_edge();
		}
	}

private:
	unsigned debounce_state_;
};

