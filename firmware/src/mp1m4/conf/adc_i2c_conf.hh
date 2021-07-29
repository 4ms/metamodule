#pragma once
#include "drivers/adc_i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;

const mdrivlib::MuxedADC_Config muxed_adc_conf{
	.SEL0{GPIO::B, 12, PinAF::AFNone},
	.SEL1{GPIO::B, 13, PinAF::AFNone},
	.SEL2{GPIO::C, 1, PinAF::AFNone},
	.adc_conf =
		{
			//
		},
};
