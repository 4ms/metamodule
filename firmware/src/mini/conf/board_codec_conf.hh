#pragma once
#include "conf/auxstream_conf.hh"
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_codec_conf.hh"
#include "drivers/codec_WM8731.hh"
#include "shared_bus.hh"

namespace MetaModule
{

using CodecT = mdrivlib::CodecWM8731;

struct Hardware : SharedBus {
	Hardware()
		: SharedBus{i2c_codec_conf} {
	}
	static inline CodecT codec{SharedBus::i2c, codec_sai_conf};
};

} // namespace MetaModule
