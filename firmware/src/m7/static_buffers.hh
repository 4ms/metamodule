#pragma once
#include "auxsignal.hh"
#include "conf/screen_buffer_conf.hh"
#include "drivers/mpu.hh"
#include "leds.hh"
#include "params.hh"

// Defined in linker:
extern char _dma_buffer_start;
extern char _dma_buffer_region_size;

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the Cortex M7/M4 architecture.
// The sections are defined in the linker file.
struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) StreamConf::Audio::AudioInBlock audio_in_dma_block;
	static inline __attribute__((section(".dma_buffer"))) StreamConf::Audio::AudioOutBlock audio_out_dma_block;
	static inline __attribute__((section(".axisram"))) uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
	static inline __attribute__((section(".dma_buffer"))) DoubleBufParamBlock param_blocks;
	static inline __attribute__((section(".dma_buffer"))) DoubleAuxStreamBlock auxsignal_block;
	static inline __attribute__((section(".axisram"))) MMScreenBufferConf::FrameBufferT screen_framebuf;

	struct CacheDisabler {
		CacheDisabler(char *_start, char *_size)
		{
			MPU_::disable_cache_for_dma_buffer(reinterpret_cast<uint32_t>(_start), reinterpret_cast<uint32_t>(_size));
		}
		CacheDisabler(void *_start, size_t _size)
		{
			MPU_::disable_cache_for_dma_buffer(reinterpret_cast<uint32_t>(_start), _size);
		}
	};
	static inline CacheDisabler dma_region_disable{&_dma_buffer_start, &_dma_buffer_region_size};
	static inline CacheDisabler screenbuf_region_disable{&screen_framebuf, sizeof(screen_framebuf)};

	static void init()
	{
		// Todo: why doesn't Params::Params() get called? because it's in a NOLOAD section of memory?
		for (auto &block : param_blocks) {
			for (auto &param : block.params) {
				param.clear();
			}
			block.metaparams.clear();
		}
	}
};

} // namespace MetaModule
