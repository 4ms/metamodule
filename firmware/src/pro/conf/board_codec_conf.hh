#pragma once
#include "conf/codec_sai_conf.hh"
#include "conf/i2c_conf.hh"
#include "core_intercom/shared_i2c_lock.hh"
#include "drivers/codec_PCM3168.hh"
#include <cstdint>
#include <span>

namespace MetaModule
{

// The codec's I2C4 is shared with the M33, so hold the bus while the codec uses it (only in init())
struct CodecPCM3168SharedI2C : mdrivlib::CodecPCM3168 {
	using CodecPCM3168::CodecPCM3168;

	Error init() {
		SharedI2CGuard lock;
		return CodecPCM3168::init();
	}
};

using CodecT = CodecPCM3168SharedI2C;

// Pro p1 has a single codec and no audio expander header.
struct Hardware {
	static inline mdrivlib::I2CPeriph i2c{codec_jack_i2c_conf};
	static inline CodecT codec{i2c, codec_sai_conf};

	// MP1's AudioStream (audio/audio.cc) also runs the audio expander's codec, if init() finds one.
	// There's no expander, so there's never one to find.
	struct NoAudioExpanderCodec {
		CodecT::Error init() {
			return CodecT::CODEC_I2C_ERR;
		}
		CodecT::Error change_samplerate_blocksize(uint32_t, uint32_t) {
			return CodecT::CODEC_NO_ERR;
		}
		template<typename T>
		void set_tx_buffer(std::span<T>, uint32_t) {
		}
		template<typename T>
		void set_rx_buffer(std::span<T>, uint32_t) {
		}
		void start() {
		}
		void stop() {
		}
	};
	static inline NoAudioExpanderCodec codec_ext;

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
