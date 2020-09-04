#include "pin.hh"
#include "fake_gpio.h"

static FakeGPIO fake_port(GPIO port);
static FakeGPIO fake_port(GPIO port)
{
	// clang-format off
	return port==GPIO::A ? FakeGPIO::A
		: port==GPIO::B ? FakeGPIO::B
		: port==GPIO::C ? FakeGPIO::C
		: port==GPIO::D ? FakeGPIO::D
		: port==GPIO::E ? FakeGPIO::E
		: port==GPIO::F ? FakeGPIO::F
		: port==GPIO::G ? FakeGPIO::G
		: port==GPIO::H ? FakeGPIO::H
		: port==GPIO::I ? FakeGPIO::I
#ifdef GPIOJ
		: port==GPIO::J ? FakeGPIO::J
#endif
#ifdef GPIOK
		: port==GPIO::K ? FakeGPIO::K
#endif
		: FakeGPIO::A;
}
// clang-format on

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
	, pin_(pin)
	, polarity_(polarity)
{
}

void Pin::high() const {}
void Pin::low() const {}
void Pin::on() const
{
}
void Pin::off() const
{
}
void Pin::set_to(uint32_t v)
{
}

bool Pin::read_raw()
{
	return false;
}
uint8_t Pin::is_on()
{
	if (polarity_ == PinPolarity::Normal)
		return read_fake_pin(fake_port(port_), pin_);
	else
		return !read_fake_pin(fake_port(port_), pin_);
}

void Pin::set_mode(PinMode mode)
{
}
void Pin::set_speed(PinSpeed speed)
{
}
void Pin::set_pull(PinPull pull)
{
}
void Pin::set_alt(uint8_t af)
{
}
void Pin::set_otype(PinOType otype)
{
}

