#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_conf.hh"
#include "drivers/codec_PCM3168.hh"

namespace MetaModule
{

using CodecT = mdrivlib::CodecPCM3168;

// Pro p1 has a single codec and no audio expander header
// (MP1 also has codec_ext and codec_ext_memory: audio.cc will need adapting).
struct Hardware {
	static inline mdrivlib::I2CPeriph i2c{codec_jack_i2c_conf};
	static inline CodecT codec{i2c, codec_sai_conf};
};

} // namespace MetaModule
