#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_conf.hh"
#include "drivers/codec_PCM3168.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

using CodecT = mdrivlib::CodecPCM3168;

// Pro p1 has a single codec and no audio expander header
// (MP1 also has codec_ext: audio.cc will need adapting).
struct Hardware {
	static inline mdrivlib::I2CPeriph i2c{codec_jack_i2c_conf};
	static inline CodecT codec{i2c, codec_sai_conf};

	// MP1's audio expander has its calibration data in an EEPROM. There's no expander, so no
	// memory to read or write.
	struct NoAudioExpanderMemory {
		bool read(uint8_t, std::span<uint8_t>) {
			return false;
		}
		bool write(auto, uint8_t = 0) {
			return false;
		}
	};
	static inline NoAudioExpanderMemory codec_ext_memory;
};

} // namespace MetaModule
