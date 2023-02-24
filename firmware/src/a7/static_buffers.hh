#pragma once
#include "auxsignal.hh"
#include "conf/ramdisk_conf.hh"
#include "conf/screen_buffer_conf.hh"
#include "conf/stream_conf.hh"
#include "inter_core_comm.hh"
#include "leds.hh"
#include "lvgl/src/misc/lv_color.h" // for lv_color_t
#include "params.hh"
#include "patch_file.hh"
#include "ramdisk.hh"
#include <span>

namespace MetaModule
{

// StaticBuffers sets up our regions of memory that have specific requirements in the target chip architecture.
// The sections are defined in the linker file.
namespace StaticBuffers
{
//If DMA Burst mode is enabled, See RM sec 18.3.12;
//The burst configuration has to be selected in order to respect the AHB protocol, where bursts must not cross the 1 Kbyte address boundary because the minimum address space that can be allocated to a single slave is 1 Kbyte. This means that the 1-Kbyte address boundary must not be crossed by a burst block transfer, otherwise an AHB error is generated, that is not reported by the DMA registers.

static inline __attribute__((section(".sysram"))) StreamConf::Audio::AudioInBlock audio_in_dma_block;
static inline __attribute__((section(".sysram"))) StreamConf::Audio::AudioOutBlock audio_out_dma_block;

using FrameBufferT = std::array<lv_color_t, ScreenBufferConf::width * ScreenBufferConf::height / 8>;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf1;
static inline __attribute__((section(".ddma"))) FrameBufferT framebuf2;
static inline __attribute__((section(".ddma"))) std::array<char, 65536> raw_patch_data;
static inline __attribute__((section(".ddma"))) std::span<char> raw_patch_span{raw_patch_data};

static inline volatile __attribute__((section(".ddma"))) InterCoreCommMessage icc_shared_message;
static inline __attribute__((section(".ddma"))) std::span<PatchFile> shared_patch_file_list;
//^^^ shared_patch_file_list is just a span (ptr and size)

static inline __attribute__((section(".sysram"))) DoubleBufParamBlock param_blocks; // 4380 * 2
static inline __attribute__((section(".sysram"))) DoubleAuxStreamBlock auxsignal_block;

static inline __attribute__((section(".virtdrive"))) RamDisk<RamDiskSizeBytes, RamDiskBlockSize> virtdrive;

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
