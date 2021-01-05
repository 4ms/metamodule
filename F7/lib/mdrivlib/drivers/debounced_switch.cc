#include "debounced_switch.hh"

DebouncedSwitch::DebouncedSwitch(GPIO port, uint8_t pin_num, PinPolarity polarity)
	: pin_(port,
		   pin_num,
		   PinMode::Input,
		   LL_GPIO_AF_0,
		   polarity == PinPolarity::Inverted ? PinPull::Up : PinPull::None,
		   polarity)
	, debounce_state_{0}
	, pressed_{false}
	, just_pressed_{false}
	, just_released_{false}
{}

void DebouncedSwitch::update()
{
	auto pin_state = pin_.is_on() ? 1 : 0;
	debounce_state_ = (debounce_state_ << 1) | pin_state;
	if (debounce_state_ == 0b0000000011111111) {
		just_pressed_ = true;
		pressed_ = true;
		just_released_ = false;
	} else if (debounce_state_ == 0b1111111100000000) {
		just_pressed_ = false;
		pressed_ = false;
		just_released_ = true;
	}
}

bool DebouncedSwitch::is_pressed() const
{
	return pressed_;
}

bool DebouncedSwitch::is_just_pressed()
{
	if (just_pressed_) {
		just_pressed_ = false;
		return true;
	} else
		return false;
}

bool DebouncedSwitch::is_just_released()
{
	if (just_released_) {
		just_released_ = false;
		return true;
	} else
		return false;
}

