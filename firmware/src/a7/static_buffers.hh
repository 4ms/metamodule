#pragma once
#include "audio.hh"
#include "conf/screen_buffer_conf.hh"
#include "conf/stream_conf.hh"
#include "leds.hh"
#include "params.hh"

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
// The attributes are defined in the linker file.
// - Audio DMA Buffer must have a static address and be in certain SRAM regions, and be non-cacheable.
// - Screen framebuffer is large, must be fast, and accessible to both cores (and in some cases, DMA friendly)
// - LED Frame buffer needs to be accessible to both cores
// - Param Blocks need to be accessible to both cores (speed may be a concern too)
namespace MetaModule
{
namespace StaticBuffers
{
static inline __attribute__((section(".sysram"))) AudioStream::AudioInStreamBlock audio_in_dma_block[4];
static inline __attribute__((section(".sysram"))) AudioStream::AudioOutStreamBlock audio_out_dma_block[4];
static inline uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
static inline MMScreenBufferConf::FrameBufferT screen_framebuf;
static inline __attribute__((section(".sysram"))) DoubleBufParamBlock param_blocks; // 4380 * 2
static inline __attribute__((section(".sysram"))) AuxSignalStreamBlock auxsignal_block[2];

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
}; // namespace StaticBuffers

} // namespace MetaModule
