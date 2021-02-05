#pragma once
#include "drivers/adc_i2c_config_struct.hh"

const ADC_I2C_Config adc_i2c_conf{
	//
};

struct MuxedADC_Config {
	PinNoInit SEL0;
	PinNoInit SEL1;
	PinNoInit SEL2;
	ADC_I2C_Config adc_conf;
};

const MuxedADC_Config muxed_adc_conf{
	.SEL0{GPIO::B, 0, PinAF::AFNone},
	.SEL1{GPIO::B, 1, PinAF::AFNone},
	.SEL2{GPIO::B, 2, PinAF::AFNone},
	.adc_conf =
		{
			//
		},
};

