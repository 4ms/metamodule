#pragma once

#include "conf/codec_sai_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/codec_PCM3168.hh"
#include "shared_bus.hh"

//#define BOARD_HAS_DAC
#include "conf/dac_conf.hh"

namespace MetaModule
{

enum class Boards { Mini, Medium, Max, PCMDev };

constexpr Boards Board = Boards::PCMDev;

using CodecT = mdrivlib::CodecPCM3168;

struct Hardware : SharedBus {
	Hardware()
		: SharedBus{i2c_codec_conf}
	{}

	static inline CodecT codecA{SharedBus::i2c, codecA_sai_conf};
	static inline CodecT codecB{SharedBus::i2c, codecB_sai_conf};

	static inline AnalogOutT dac;
	// 	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
};

} // namespace MetaModule
