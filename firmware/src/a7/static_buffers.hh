#pragma once
#include "audio.hh"
#include "conf/screen_buffer_conf.hh"
// #include "drivers/mpu.hh"
#include "leds.hh"
#include "params.hh"

// Defined in linker:
// extern char _dma_buffer_start;
// extern char _dma_buffer_region_size;

// StaticBuffers sets up our regions of memory that have specific requirements in the Cortex M7/M4 architecture.
// The attributes are defined in the linker file.
// - Audio DMA Buffer must have a static address and be in certain SRAM regions, and be non-cacheable.
// - Screen framebuffer is large, must be fast, and accessible to M7 and the M4 controlling the MDMA
// - LED Frame buffer needs to be accessible to both cores
// - Param Blocks need to be accessible to both cores (speed may be a concern too)
namespace MetaModule
{
struct StaticBuffers {
	static inline __attribute__((section(".ddma"))) AudioStream::AudioStreamBlock audio_dma_block[4];
	static inline /*__attribute__((section(".axisram"))) */ uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
	static inline /*__attribute__((section(".dma_buffer"))) */ DoubleBufParamBlock param_blocks; // 4380 * 2
	static inline __attribute__((section(".sysram"))) MMScreenBufferConf::FrameBufferT screen_framebuf;
	// static inline __attribute__((section(".shared_memory"))) MMScreenConf::FrameBufferT screen_framebuf_shared;

	// Try using m4 core to initaite MDMA from sysram to shared_memory (SRAM3/4)
	// if that doesn't work, put screen buf in shared_memory and see if it's much slower
	// if that's not good, then initiate the mdma transfer here on a7 (sysram to shared memory) before releasing the
	// screenframbuflock
	//
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
