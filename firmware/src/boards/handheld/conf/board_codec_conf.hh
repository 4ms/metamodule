#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/codec_TAC5211.hh"
#include "drivers/codec_null.hh"

namespace MetaModule
{

using CodecT = mdrivlib::CodecTAC5211;
using ExtCodecT = mdrivlib::CodecNull;

struct Hardware {
	static inline mdrivlib::I2CPeriph i2c{a7m4_shared_i2c_conf}; //for internal GPIO expander, which is not used...

	static inline mdrivlib::I2CPeriph codec_i2c{a7m4_shared_i2c_conf};
	static inline CodecT codec{codec_i2c, codec_mainPCB_sai_conf};

	static inline ExtCodecT codec_ext;
};

} // namespace MetaModule
