#include "pin.hh"
#include "system.hh"

Pin::Pin(
	GPIO port,
	uint8_t pin,
	PinMode mode,
	uint8_t af,
	PinPull pull,
	PinPolarity polarity,
	PinSpeed speed,
	PinOType otype)
	: port_(port)
	, pin_(static_cast<uint16_t>(1 << (pin & 0x0F)))
	, polarity_(polarity)
{
	System::enable_gpio_rcc(GPIOPort(port_));
	set_mode(mode);
	set_pull(pull);

	if (mode == PinMode::Alt || mode == PinMode::Output) {
		set_speed(speed);
		set_otype(otype);
	}
	if (mode == PinMode::Alt)
		set_alt(af);
}

void Pin::high() const { LL_GPIO_SetOutputPin(GPIOPort(port_), pin_); }
void Pin::low() const { LL_GPIO_ResetOutputPin(GPIOPort(port_), pin_); }
void Pin::on() const
{
	if (polarity_ == PinPolarity::Normal)
		high();
	else
		low();
}
void Pin::off() const
{
	if (polarity_ == PinPolarity::Normal)
		low();
	else
		high();
}
void Pin::set_to(uint32_t v)
{
	// v ? on() : off();
	if (v)
		on();
	else
		off();
}

bool Pin::read_raw()
{
	return LL_GPIO_IsInputPinSet(GPIOPort(port_), pin_) ? true : false;
}
uint8_t Pin::is_on()
{
	return (polarity_ == PinPolarity::Normal) ? read_raw() : !read_raw();
}

void Pin::set_mode(PinMode mode)
{
	LL_GPIO_SetPinMode(GPIOPort(port_), pin_, HALParam(mode));
}
void Pin::set_speed(PinSpeed speed)
{
	LL_GPIO_SetPinSpeed(GPIOPort(port_), pin_, HALParam(speed));
}
void Pin::set_pull(PinPull pull)
{
	LL_GPIO_SetPinPull(GPIOPort(port_), pin_, HALParam(pull));
}
void Pin::set_alt(uint8_t af)
{
	if (pin_ >= LL_GPIO_PIN_8)
		LL_GPIO_SetAFPin_8_15(GPIOPort(port_), pin_, af);
	else
		LL_GPIO_SetAFPin_0_7(GPIOPort(port_), pin_, af);
}
void Pin::set_otype(PinOType otype)
{
	LL_GPIO_SetPinOutputType(GPIOPort(port_), pin_, HALParam(otype));
}

