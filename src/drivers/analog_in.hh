#pragma once
#include "adc_builtin_driver.hh"
#include "filter.hh"

template<AdcPeriphNum p, AdcChanNum c, int kOverSampleAmt = 128>
struct AnalogIn : AdcChan<p, c, uint32_t> {
	AnalogIn(GPIO port, uint8_t pin_num)
	{
		Pin pin(port, pin_num, PinMode::Analog);
	}
	void read()
	{
		oversampler_.add_val(this->get_val());
	}
	// void read_TESTME() { oversampler_.add_val(AdcPeriph<p>::get_val(c)); }

	uint16_t get()
	{
		return oversampler_.val();
	}

private:
	Oversampler<uint32_t, kOverSampleAmt> oversampler_;
};
