#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/codec_PCM3168.hh"

namespace MetaModule
{

using CodecT = mdrivlib::CodecPCM3168;

struct Hardware {
	Hardware() = default;
	static inline mdrivlib::I2CPeriph i2c{a7m4_shared_i2c_codec_conf};
	static inline CodecT codec{i2c, codec_mainPCB_sai_conf}; //44W (reg 88)
	static inline CodecT codec_ext{i2c, codec_ext_sai_conf}; //45W (reg 8A)
};

} // namespace MetaModule
