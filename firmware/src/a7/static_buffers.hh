#pragma once
#include "auxsignal.hh"
#include "conf/screen_buffer_conf.hh"
#include "conf/stream_conf.hh"
#include "leds.hh"
#include "params.hh"

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
// The sections are defined in the linker file.
namespace StaticBuffers
{
static inline __attribute__((section(".sysram"))) StreamConf::Audio::AudioInBlock audio_in_dma_block;
static inline __attribute__((section(".sysram"))) StreamConf::Audio::AudioOutBlock audio_out_dma_block;
static inline uint32_t led_frame_buffer[PCA9685Driver::kNumLedsPerChip];
static inline MMScreenBufferConf::FrameBufferT screen_framebuf;
static inline __attribute__((section(".sysram"))) DoubleBufParamBlock param_blocks; // 4380 * 2
static inline __attribute__((section(".sysram"))) DoubleAuxSignalStreamBlock auxsignal_block;

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
