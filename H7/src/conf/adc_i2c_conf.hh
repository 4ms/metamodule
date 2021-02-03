#pragma once
#include "drivers/adc_i2c_config_struct.hh"
#include "drivers/adc_i2c_max11645.hh"

const ADC_I2C_Config adc_i2c_conf{
	//
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

