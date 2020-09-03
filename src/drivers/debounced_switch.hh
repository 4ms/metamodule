#include "pin.hh"
#include <stdint.h>

struct DebouncedSwitch {
	DebouncedSwitch(GPIO port, uint8_t pin_num, PinPolarity polarity = PinPolarity::Inverted);
	void update();
	bool is_pressed() const;
	bool is_just_pressed();
	bool is_just_released();

private:
	Pin pin_;
	bool pressed_;
	bool just_pressed_;
	bool just_released_;
	uint16_t debounce_state_;
};

