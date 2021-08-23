#pragma once
#include "drivers/adc_i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;

const mdrivlib::MuxedADC_Config muxed_adc_conf{
	.SEL0{GPIO::B, 15, PinAF::AFNone},
	.SEL1{GPIO::B, 3, PinAF::AFNone},
	.SEL2{GPIO::B, 4, PinAF::AFNone},
	.adc_conf =
		{
			//
		},
};
