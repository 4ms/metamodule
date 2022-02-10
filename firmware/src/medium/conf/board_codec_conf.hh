#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/codec_PCM3168.hh"
// #include "drivers/qspi_flash_driver.hh"
#include "shared_bus.hh"

namespace MetaModule
{

// enum class Boards { Mini, Medium, Max, PCMDev };
// constexpr Boards Board = Boards::Medium;

using CodecT = mdrivlib::CodecPCM3168;

struct Hardware : SharedBus {
	Hardware()
		: SharedBus{i2c_codec_conf} {
	}

	static inline CodecT codec{SharedBus::i2c, codec_mainPCB_sai_conf}; //44W (reg 88)
	static inline CodecT codec_ext{SharedBus::i2c, codec_ext_sai_conf}; //45W (reg 8A)

	// 	QSpiFlash qspi{qspi_flash_conf}; // not used yet, but will hold patches, and maybe graphics/fonts
};

} // namespace MetaModule
