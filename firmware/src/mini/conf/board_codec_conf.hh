#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/codec_WM8731.hh"
#include "shared_bus.hh"

#define BOARD_HAS_DAC
#include "conf/dac_conf.hh"

// #include "drivers/qspi_flash_driver.hh"

namespace MetaModule
{

enum class Boards { Mini, Medium, Max, PCMDev };

constexpr Boards Board = Boards::PCMDev;

using CodecT = mdrivlib::CodecWM8731;

struct Hardware : SharedBus {
	Hardware()
		: SharedBus{i2c_conf_codec}
	{}

	mdrivlib::CodecWM8731 codec{SharedBus::i2c, codec_sai_conf};
	AnalogOutT dac;
	// 	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
} _hw;
} // namespace MetaModule
