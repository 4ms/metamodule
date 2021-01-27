#pragma once
#include "conf/control_conf.hh"
#include "drivers/analog_in_ext.hh"
#include "drivers/debounced_switch.hh"
#include "drivers/i2c.hh"
#include "drivers/pin.hh"
#include "drivers/rotary.hh"
#include "drivers/stm32xx.h"
#include "drivers/timekeeper.hh"
#include "stm32h745xx.h"
#include "util/filter.hh"

struct GPIO_expander_conf {
	uint32_t addr;
	Pin int_pin;
	IRQType IRQn;
};

template<unsigned NumGPIOs>
struct GPIOExpander {
	GPIOExpander(const GPIO_expander_conf &conf)
		: _conf{conf}
	{}

	void start()
	{
		// Create an EXTI interrupt to respond to chip telling us there's a pin change
		InterruptManager::registerISR(_conf.IRQn, [this]() { read_pins(); });
	}
	void read_pins()
	{
		// queue an I2C read:
		// i2c_.queue_read(conf.dev_addr, conf.reg_addr, num_bits, [this](uint8_t *received_data){
		//  for (int i=0; i<NumGPIOs; i++)
		// 		last_readings[i] = (received_data[i / 8] & (1<<(i & 0b111)))
		// 	});
	}

	bool last_readings[NumGPIOs];

private:
	const GPIO_expander_conf &_conf;
};

const GPIO_expander_conf gpio_expander_conf = {
	.addr = 0x00,
	.int_pin = {GPIO::D, 11, PinMode::Input},
	.IRQn = EXTI15_10_IRQn,
};

struct Controls {
	AnalogIn<AdcSpi_MAX11666<2>, 4, Oversampler<16>> cvadc{spi_adc_conf};

	GPIOExpander<16> sense{gpio_expander_conf};
	DebouncedSwitch button[2] = {{GPIO::C, 10}, {GPIO::C, 11}};
	RotaryEncoder<RotaryFullStep> rotary = {GPIO::C, 7, GPIO::C, 8};
	DebouncedSwitch rotary_button = {GPIO::C, 6};

	Controls();
	void read();
	void start();

private:
	Timekeeper read_controls_task;
};
