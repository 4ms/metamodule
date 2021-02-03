#pragma once
#include "drivers/adc_i2c_config_struct.hh"
#include "drivers/adc_i2c_max11645.hh"
#include "drivers/i2c.hh"

// Handles 2-channel I2C ADC MAX11645)
// Channel 0 is connected to an 8x1 switch, with a pot on each input
// and 3 GPIO pins selecting one.
// Channel 1 is connected to Patch CV
class MuxedADC {
public:
	MuxedADC(I2CPeriph &i2c, const MuxedADC_Config &conf)
		: chan_sel{{conf.SEL0.gpio, conf.SEL0.pin, PinMode::Output},
				   {conf.SEL1.gpio, conf.SEL1.pin, PinMode::Output},
				   {conf.SEL2.gpio, conf.SEL2.pin, PinMode::Output}}
		, _i2c{i2c}
		, _adc{_i2c, conf.adc_conf}
	{}

	void select_channel0_source(unsigned chan)
	{
		chan_sel[0].set_to(chan & 0b001);
		chan_sel[1].set_to(chan & 0b010);
		chan_sel[2].set_to(chan & 0b100);
	}

	void initiate_read() {}
	uint32_t get_val(unsigned chan)
	{
		return chan < 8 ? last_pot_reading[chan] : last_chan1_reading;
	}

private:
	Pin chan_sel[3];
	I2CPeriph &_i2c;
	ADC_I2C_MAX11645 _adc;

	uint32_t last_pot_reading[8];
	uint32_t last_chan1_reading;
};

