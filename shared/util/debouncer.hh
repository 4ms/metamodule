#include <cstdint>

template<unsigned RisingEdgePattern = 0x0000000F, unsigned FallingEdgePattern = 0xFFFFFFF0>
struct Debouncer {
	Debouncer()
		: debounce_state_{0}
		, is_high_{false}
		, got_rising_edge_{false}
		, got_falling_edge_{false}
	{}

	void register_state(unsigned new_state)
	{
		debounce_state_ = (debounce_state_ << 1) | new_state;
		if (debounce_state_ == RisingEdgePattern) {
			got_rising_edge_ = true;
			is_high_ = true;
			got_falling_edge_ = false;
		} else if (debounce_state_ == FallingEdgePattern) {
			got_rising_edge_ = false;
			is_high_ = false;
			got_falling_edge_ = true;
		}
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

	bool is_just_released()
	{
		if (got_falling_edge_) {
			got_falling_edge_ = false;
			return true;
		} else
			return false;
	}

private:
	bool is_high_;
	bool got_rising_edge_;
	bool got_falling_edge_;
	unsigned debounce_state_;
};

