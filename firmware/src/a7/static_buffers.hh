#pragma once
#include "auxsignal.hh"
#include "conf/qspi_flash_conf.hh"
#include "conf/screen_buffer_conf.hh"
#include "conf/stream_conf.hh"
#include "leds.hh"
#include "lvgl/src/misc/lv_color.h" // for lv_color_t
#include "params.hh"
#include "ramdisk.hh"

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
// The sections are defined in the linker file.
namespace StaticBuffers
{
static inline __attribute__((section(".sysram"))) StreamConf::Audio::AudioInBlock audio_in_dma_block;
static inline __attribute__((section(".sysram"))) StreamConf::Audio::AudioOutBlock audio_out_dma_block;

using FrameBufferT = std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height / 10>;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf1;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf2;

static inline __attribute__((section(".sysram"))) DoubleBufParamBlock param_blocks; // 4380 * 2
static inline __attribute__((section(".sysram"))) DoubleAuxStreamBlock auxsignal_block;

static inline __attribute__((section(".virtdrive"))) RamDisk<qspi_patchflash_conf.flash_size_bytes, 512> virtdrive;

static void init() {
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
