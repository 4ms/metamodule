#pragma once
#include "drivers/adc_i2c_config_struct.hh"

const MuxedADC_Config muxed_adc_conf{
	.SEL0{GPIO::B, 0, PinAF::AFNone},
	.SEL1{GPIO::B, 1, PinAF::AFNone},
	.SEL2{GPIO::B, 2, PinAF::AFNone},
	.adc_conf =
		{
			//
		},
};
