#pragma once
#include "drivers/adc_i2c_tla2528.hh"

namespace MetaModule::KnobExpander
{

constexpr mdrivlib::TLA2528::Config conf{
	.addr = mdrivlib::TLA2528::Config::LowestAllowedAddr,
	.oversample = true,
};

}
