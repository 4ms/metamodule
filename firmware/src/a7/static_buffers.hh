#pragma once
#include "audio.hh"
#include "conf/screen_buffer_conf.hh"
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
static inline __attribute__((section(".ddma"))) AudioStream::AudioStreamBlock audio_dma_block[4];
static inline __attribute__((section(".sysram"))) uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
static inline __attribute__((section(".sysram"))) MMScreenBufferConf::FrameBufferT screen_framebuf;

// FIXME: Why does last few words of param_blocks become 00'd out if its in sysram and appears earlier in this list?
// (address 0x2FFDE400 and up is blanked)
static inline __attribute__((section(".ddma"))) DoubleBufParamBlock param_blocks; // 4380 * 2

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
