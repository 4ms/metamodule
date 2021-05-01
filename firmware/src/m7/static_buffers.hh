#pragma once
#include "audio.hh"
#include "conf/screen_buffer_conf.hh"
#include "drivers/mpu.hh"
#include "leds.hh"
#include "params.hh"

// Defined in linker:
extern char _dma_buffer_start;
extern char _dma_buffer_region_size;

// StaticBuffers sets up our regions of memory that have specific requirements in the Cortex M7/M4 architecture.
// The attributes are defined in the linker file.
// - Audio DMA Buffer must have a static address and be in certain SRAM regions, and be non-cacheable.
// - Screen framebuffer is large, must be fast, and accessible to M7 and the M4 controlling the MDMA
// - LED Frame buffer needs to be accessible to both cores
// - Param Blocks need to be accessible to both cores (speed may be a concern too)
namespace MetaModule
{
struct StaticBuffers {
	static inline __attribute__((section(".dma_buffer"))) AudioStream::AudioStreamBlock audio_dma_block[4];
	static inline __attribute__((section(".axisram"))) uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
	static inline __attribute__((section(".dma_buffer"))) DoubleBufParamBlock param_blocks;
	static inline __attribute__((section(".axisram"))) MMScreenBufferConf::FrameBufferT screen_framebuf;

	struct CacheDisabler {
		CacheDisabler(char *_start, char *_size)
		{
			target::MPU_::disable_cache_for_dma_buffer(reinterpret_cast<uint32_t>(_start),
													   reinterpret_cast<uint32_t>(_size));
		}
		CacheDisabler(void *_start, size_t _size)
		{
			target::MPU_::disable_cache_for_dma_buffer(reinterpret_cast<uint32_t>(_start), _size);
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
