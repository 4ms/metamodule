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
	enum class Channel : uint8_t {
		Pots = 0,
		PatchCV = 1,
	};

	MuxedADC(I2CPeriph &i2c, const MuxedADC_Config &conf)
		: _pot_sel{{conf.SEL0.gpio, conf.SEL0.pin, PinMode::Output},
				   {conf.SEL1.gpio, conf.SEL1.pin, PinMode::Output},
				   {conf.SEL2.gpio, conf.SEL2.pin, PinMode::Output}}
		, _adc{i2c, conf.adc_conf}
	{}

	void start()
	{
		auto err = _adc.send_config();
		handle_error(err);
	}

	void select_pot_source(unsigned pot)
	{
		_cur_pot = pot & 0b111;
		_pot_sel[0].set_to(pot & 0b001);
		_pot_sel[1].set_to(pot & 0b010);
		_pot_sel[2].set_to(pot & 0b100);
	}

	void initiate_read(Channel chan)
	{
		auto err = _adc.select_channel(static_cast<uint8_t>(chan));
		handle_error(err);
		err = _adc.read_blocking();
		handle_error(err);
	}

	void finalize_read(Channel chan)
	{
		if (chan == Channel::Pots)
			_last_pot_reading[_cur_pot] = _adc.get_last_val();
		else
			_last_chan1_reading = _adc.get_last_val();
	}

	uint32_t get_last_pot_reading(unsigned pot)
	{
		return pot < 8 ? _last_pot_reading[pot] : 0;
	}

	uint32_t get_last_cvjack_reading()
	{
		return _last_chan1_reading;
	}

private:
	Pin _pot_sel[3];
	ADC_I2C_MAX11645 _adc;

	uint32_t _last_pot_reading[8];
	uint32_t _last_chan1_reading;
	unsigned _cur_pot;

	void handle_error(ADC_I2C_MAX11645::Error err)
	{
		if (err != ADC_I2C_MAX11645::Error::None) {
			__BKPT();
		}
	}
};

