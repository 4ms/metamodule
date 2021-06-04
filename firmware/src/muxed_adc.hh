#pragma once
#include "conf/adc_i2c_conf.hh"
#include "drivers/adc_i2c_config_struct.hh"
#include "drivers/adc_i2c_max11645.hh"
#include "drivers/i2c.hh"

// Thin wrapper over 2-channel ADC MAX11645 (I2C) and 8x1 MUX (via GPIOs)
// ADC Channel 0 is connected to the 8=>1 mux, with a pot wiper on each input.
// The 3 GPIO pins selecting which pot is active.
// ADC Channel 1 is connected to Patch CV
namespace mdrivlib
{
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
		_pot_sel[0].set_to(pot & 0b001);
		_pot_sel[1].set_to(pot & 0b010);
		_pot_sel[2].set_to(pot & 0b100);
	}

	void select_adc_channel(Channel chan)
	{
		auto err = _adc.select_channel(static_cast<uint8_t>(chan));
		handle_error(err);
	}

	void request_reading()
	{
		auto err = _adc.read();
		handle_error(err);
	}

	uint32_t collect_reading()
	{
		return _adc.collect_last_reading();
	}

private:
	Pin _pot_sel[3];
	ADC_I2C_MAX11645 _adc;

	void handle_error(ADC_I2C_MAX11645::Error err)
	{
		if (err != ADC_I2C_MAX11645::Error::None) {
			//__BKPT();
		}
	}
};
} // namespace mdrivlib
