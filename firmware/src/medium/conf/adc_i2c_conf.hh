#pragma once
#include "drivers/adc_i2c_config_struct.hh"

using mdrivlib::GPIO;
using mdrivlib::PinAF;

const mdrivlib::DualMuxedADC_Config muxed_adc_conf{
	.SEL0{GPIO::E, 13, PinAF::AFNone},
	.SEL1{GPIO::H, 8, PinAF::AFNone},
	.SEL2{GPIO::D, 10, PinAF::AFNone},

	.bSEL0{GPIO::B, 15, PinAF::AFNone},
	.bSEL1{GPIO::B, 3, PinAF::AFNone},
	.bSEL2{GPIO::B, 4, PinAF::AFNone},

	.adc_conf = {},
};
